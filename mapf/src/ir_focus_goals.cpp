#include "../include/ir_focus_goals.hpp"

const std::string IR_FocusGoals::SOLVER_NAME = "IR_FocusGoals";

IR_FocusGoals::IR_FocusGoals(Problem* _P)
  : IR(_P)
{
  solver_name = IR_FocusGoals::SOLVER_NAME;
}

void IR_FocusGoals::refinePlan()
{
    Plan plan = solution;

  std::vector<int> CLOSE;

  while (current_iteration < max_iteration && !overCompTime()) {
    if (overCompTime()) break;

    if (simple_refine) {
      for (int i = 0; i < P->getNum(); ++i) {
        if (plan.getPathCost(i) - pathDist(i) == 0) continue;

        // identify modification list
        const auto modif_list = LibIR::identifyAgentsAtGoal(i, plan, P);
        if (modif_list.empty()) continue;

        Problem _P = Problem(P, getRefineTimeLimit());
        auto res = getOptimalPlan(&_P, plan, modif_list);
        plan = std::get<1>(res);
        updateSolution(plan);

        if (current_iteration >= max_iteration) break;
      }

      // default
    } else {
      // calculate the largest gap
      int target_id = -1;
      int largest_gap = 0;
      for (int i = 0; i < P->getNum(); ++i) {
        if (inArray(i, CLOSE)) continue;
        const int gap = plan.getPathCost(i) - pathDist(i);
        if (gap == 0) continue;
        if (gap > largest_gap) {
          target_id = i;
          largest_gap = gap;
        }
      }

      // clear closed list if such agent cannot be found
      if (target_id == -1) {
        CLOSE.clear();
        continue;
      }

      // identify modification list
      const auto modif_list = LibIR::identifyAgentsAtGoal(target_id, plan, P);
      if (modif_list.empty()) {
        CLOSE.push_back(target_id);
        continue;
      }

      Problem _P = Problem(P, getRefineTimeLimit());
      auto res = getOptimalPlan(&_P, plan, modif_list);
      plan = std::get<1>(res);
      if (plan.getSOC() == last_soc) CLOSE.push_back(target_id);
      updateSolution(plan);
    }
  }
}

void IR_FocusGoals::setParams(int argc, char* argv[])
{
  IR::setParams(argc, argv);

  struct option longopts[] = {
    {"use-simple", no_argument, 0, 'u'},
    {0, 0, 0, 0},
  };
  optind = 1;  // reset
  int opt, longindex;
  std::string s, s_tmp;

  while ((opt = getopt_long(argc, argv, "u", longopts,  &longindex)) != -1) {
    switch (opt) {
    case 'u':
      simple_refine = true;
      break;
    }
  }
}

void IR_FocusGoals::printHelp()
{
  std::cout
    << IR_FocusGoals::SOLVER_NAME << "\n"
    << "  -u --use-simple"
    << "                "
    << "use simple refinement"
    << std::endl;
}
