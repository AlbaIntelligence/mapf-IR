#include "../include/ir.hpp"

#include <fstream>
#include <set>

const std::string IR::SOLVER_NAME = "IR";
const IR::INIT_SOLVER_TYPE IR::DEFAULT_INIT_SOLVER =
    IR::INIT_SOLVER_TYPE::PIBT_COMPLETE;
const IR::OPTIMAL_SOLVER_TYPE IR::DEFAULT_REFINE_SOLVER =
    IR::OPTIMAL_SOLVER_TYPE::ICBS;
const int IR::DEFAULT_MAX_ITERATION = 100;
const int IR::DEFAULT_TIMEOUT_REFINEMENT = 3000;
const int IR::DEFAULT_SAMPLING_NUM = 10;

// used for set underlying solver options
static void setSolverOption(std::shared_ptr<Solver> solver,
                            const std::vector<std::string>& option)
{
  if (option.empty()) return;
  int argc = option.size() + 1;
  char* argv[argc + 1];
  for (int i = 0; i < argc; ++i) {
    char* tmp = const_cast<char*>(option[i].c_str());
    argv[i + 1] = tmp;
  }
  solver->setParams(argc, argv);
}

IR::IR(Problem* _P)
  : Solver(_P),
    init_solver(DEFAULT_INIT_SOLVER),
    refine_solver(DEFAULT_REFINE_SOLVER),
    current_iteration(0),
    max_iteration(DEFAULT_MAX_ITERATION),
    output_file(DEFAULT_OUTPUT_FILE),
    make_log_every_itr(false),
    timeout_refinement(DEFAULT_TIMEOUT_REFINEMENT),
    verbose_underlying_solver(false),
    sampling_num(std::min(DEFAULT_SAMPLING_NUM, P->getNum()))
{
  solver_name = IR::SOLVER_NAME;
}

IR::~IR() {}

void IR::run()
{
  // get initial plan
  solution = getInitialPlan();
  solved = !solution.empty();
  if (!solved) return;  // failure
  const int init_plan_soc = solution.getSOC();
  const int init_plan_makespan = solution.getMakespan();
  HIST.push_back(std::make_tuple(getSolverElapsedTime(), init_plan_soc, init_plan_makespan));
  info("  init plan",
       ", comp_time:", getSolverElapsedTime(),
       ", soc:", init_plan_soc,
       ", makespan:", init_plan_makespan);
  last_soc = init_plan_soc;
  last_makespan = init_plan_makespan;

  if (make_log_every_itr) makeLog(output_file);

  // refinement
  refinePlan();

  // print final info
  const int soc = solution.getSOC();
  const int makespan = solution.getMakespan();
  info("  refinement results, soc:",
       init_plan_soc, "->", soc,
       " (improved:" , init_plan_soc - soc, ")",
       ", makespan:",
       init_plan_makespan, "->", solution.getMakespan(),
       " (improved:" , init_plan_makespan - makespan, ")");
}

void IR::updateSolution(const Plan& plan)
{
  ++current_iteration;

  solution = plan;
  const int soc = solution.getSOC();
  const int makespan = solution.getMakespan();
  HIST.push_back(std::make_tuple(getSolverElapsedTime(), soc, makespan));

  if (make_log_every_itr) makeLog(output_file);

  printProcessInfo();

  last_soc = soc;
  last_makespan = makespan;
}

void IR::printProcessInfo()
{
  const int soc = solution.getSOC();
  const int makespan = solution.getMakespan();

  info("  iter: ", current_iteration,
       ", comp_time:", getSolverElapsedTime(),
       ", soc:", soc, "(improved: ", last_soc - soc,
       ", LB: ", getLowerBoundSOC(), ")",
       ", makespan:", makespan, "(improved: ", last_makespan - makespan,
       ", LB: ", getLowerBoundMakespan(), ")");
}

// failed -> return empty plan
Plan IR::getInitialPlan()
{
  // set problem
  Problem _P = Problem(P, max_comp_time);

  // set solver
  std::shared_ptr<Solver> solver;
  switch (init_solver) {
    case INIT_SOLVER_TYPE::HCA:
      solver = std::make_shared<HCA>(&_P);
      break;
    case INIT_SOLVER_TYPE::WHCA:
      solver = std::make_shared<WHCA>(&_P);
      break;
    case INIT_SOLVER_TYPE::ECBS:
      solver = std::make_shared<ECBS>(&_P);
      break;
    case INIT_SOLVER_TYPE::PIBT:
      solver = std::make_shared<PIBT>(&_P);
      break;
    case INIT_SOLVER_TYPE::RevisitPP:
      solver = std::make_shared<RevisitPP>(&_P);
      break;
    case INIT_SOLVER_TYPE::PIBT_COMPLETE:
    default:
      solver = std::make_shared<PIBT_COMPLETE>(&_P);
      break;
  }

  // set solver options
  setSolverOption(solver, option_init_solver);
  solver->setVerbose(verbose_underlying_solver);

  // solve
  solver->solve();

  // success
  Plan plan;
  if (solver->succeed()) plan = solver->getSolution();

  return plan;
}

void IR::refinePlan()
{
  Plan plan = solution;

  // random sampling
  std::vector<int> A(P->getNum());
  std::iota(A.begin(), A.end(), 0);

  while (current_iteration < max_iteration) {
    if (overCompTime()) break;

    // create sample
    std::shuffle(A.begin(), A.end(), *MT);
    std::vector<int> modif_list(sampling_num);
    std::copy(A.begin(), A.begin() + sampling_num, modif_list.begin());

    // refine by optimal solver
    Problem _P = Problem(P, std::min(getRemainedTime(), timeout_refinement));
    plan = std::get<1>(getOptimalPlan(&_P, plan, modif_list));

    // update plan;
    updateSolution(plan);
  }
}

std::tuple<bool, Plan> IR::getOptimalPlan(Problem* _P, const Plan& current_plan,
                                          const std::vector<int>& sample)
{
  // set solver
  std::shared_ptr<Solver> solver;
  switch (refine_solver) {
    case OPTIMAL_SOLVER_TYPE::CBS_NORMAL:
      solver = std::make_shared<CBS>(_P);
      break;
    case OPTIMAL_SOLVER_TYPE::CBS:
      solver = std::make_shared<CBS_REFINE>(_P, current_plan, sample);
      break;
    case OPTIMAL_SOLVER_TYPE::ICBS_NORMAL:
      solver = std::make_shared<ICBS>(_P);
      break;
    case OPTIMAL_SOLVER_TYPE::ICBS:
    default:
      solver = std::make_shared<ICBS_REFINE>(_P, current_plan, sample);
      break;
  }

  // set solver option
  setSolverOption(solver, option_optimal_solver);
  solver->setVerbose(verbose_underlying_solver);

  // solve
  solver->solve();

  Plan plan = current_plan;
  bool success = false;

  // success
  if (solver->succeed()) {
    plan = solver->getSolution();
    success = true;
  }

  return std::make_tuple(success, plan);
}

void IR::setParams(int argc, char* argv[])
{
  struct option longopts[] = {
      {"timeout-refinement", required_argument, 0, 't'},
      {"log-every-iter", required_argument, 0, 'l'},
      {"init-solver", required_argument, 0, 'x'},
      {"optimal-solver", required_argument, 0, 'y'},
      {"option-init-solver", required_argument, 0, 'X'},
      {"option-optimal-solver", required_argument, 0, 'Y'},
      {"verbose-underlying", no_argument, 0, 'V'},
      {"max-iteration", required_argument, 0, 'n'},
      {"sampling-num", required_argument, 0, 'S'},
      {0, 0, 0, 0},
  };
  optind = 1;  // reset
  int opt, longindex;
  std::string s, s_tmp;

  while ((opt = getopt_long(argc, argv, "o:lt:x:y:X:Y:Vn:S:", longopts,
                            &longindex)) != -1) {
    switch (opt) {
      case 'o':
        output_file = std::string(optarg);
        break;
      case 'l':
        make_log_every_itr = true;
        break;
      case 't':
        timeout_refinement = std::atoi(optarg);
        if (timeout_refinement < 0 || max_comp_time < timeout_refinement) {
          warn("invalid early-stop time, using max_comp_time");
          timeout_refinement = max_comp_time;
        }
        break;
      case 'x':
        s = std::string(optarg);
        if (s == "PIBT") {
          init_solver = INIT_SOLVER_TYPE::PIBT;
        } else if (s == "HCA") {
          init_solver = INIT_SOLVER_TYPE::HCA;
        } else if (s == "WHCA") {
          init_solver = INIT_SOLVER_TYPE::WHCA;
        } else if (s == "ECBS") {
          init_solver = INIT_SOLVER_TYPE::ECBS;
        } else if (s == "RevisitPP") {
          init_solver = INIT_SOLVER_TYPE::RevisitPP;
        } else if (s == "PIBT_COMPLETE") {
          init_solver = INIT_SOLVER_TYPE::PIBT_COMPLETE;
        } else {
          warn("solver does not exists, use PIBT");
        }
        break;
      case 'X':
        s = std::string(optarg);
        for (int i = 0; i < s.size(); ++i) {
          if (s[i] == ' ') {
            option_init_solver.push_back(s_tmp);
            s_tmp = "";
          } else {
            s_tmp += s[i];
            if (i == s.size() - 1) option_init_solver.push_back(s_tmp);
          }
        }
        break;
      case 'y':
        s = std::string(optarg);
        if (s == "CBS") {
          refine_solver = OPTIMAL_SOLVER_TYPE::CBS;
        } else if (s == "CBS_NORMAL") {
          refine_solver = OPTIMAL_SOLVER_TYPE::CBS_NORMAL;
        } else if (s == "ICBS") {
          refine_solver = OPTIMAL_SOLVER_TYPE::ICBS;
        } else if (s == "ICBS_NORMAL") {
          refine_solver = OPTIMAL_SOLVER_TYPE::ICBS_NORMAL;
        } else {
          warn("solver does not exists, use ICBS");
        }
        break;
      case 'Y':
        s = std::string(optarg);
        for (int i = 0; i < s.size(); ++i) {
          if (s[i] == ' ') {
            option_optimal_solver.push_back(s_tmp);
            s_tmp = "";
          } else {
            s_tmp += s[i];
            if (i == s.size() - 1) option_optimal_solver.push_back(s_tmp);
          }
        }
        break;
      case 'V':
        verbose_underlying_solver = true;
        break;
      case 'n':
        max_iteration = std::atoi(optarg);
        break;
      case 'S':
        sampling_num = std::min(std::atoi(optarg), P->getNum());
        break;
      default:
        break;
    }
  }
}

void IR::printHelp()
{
  std::cout
      << IR::SOLVER_NAME << "\n"
      << "  -l --log-every-iter"
      << "           "
      << "make log for every iteration\n"

      << "  -t --timeout-refinement [INT]"
      << " "
      << "timeout for refinement\n"

      << "  -x --init-solver [SOLVER]"
      << "     "
      << "init solver: { PIBT, HCA, WHCA, PIBT_COMPLETE }, default: "
         "PIBT_COMPLETE\n"

      << "  -X --option-init-solver [\"OPTION\"]\n"
      << "                                "
      << "option for init-solver\n"

      << "  -y --refine-solver [SOLVER]"
      << "   "
      << "refine solver: { CBS, CBS_USUAL, ICBS, ICBS_USUAL }, default: ICBS\n"

      << "  -Y --option-refine-solver [\"OPTION\"]\n"
      << "                                "
      << "option for refine-solver\n"

      << "  -n --max-iteration [INT]"
      << "      "
      << "max iteration\n"

      << "  -S --sampling-num [INT]"
      << "       "
      << "number of sampling"

      << std::endl;
}

void IR::makeLog(const std::string& logfile)
{
  std::ofstream log;
  log.open(logfile, std::ios::out);
  makeLogBasicInfo(log);

  // record the data of each iteration
  for (int t = 0; t < HIST.size(); ++t) {
    auto hist = HIST[t];
    log << "iter=" << t << ","
        << "comp_time=" << std::get<0>(hist) << ","
        << "soc=" << std::get<1>(hist) << ","
        << "makespan=" << std::get<1>(hist) << "\n";
  }

  makeLogSolution(log);
  log.close();
}
