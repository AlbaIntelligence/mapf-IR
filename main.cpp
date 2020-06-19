#include <iostream>
#include <getopt.h>
#include <vector>
#include <random>
#include <util.hpp>
#include <problem.hpp>
#include <pibt.hpp>

void printHelp();
Solver* getSolver(const std::string solver_name,
                  Problem* P,
                  int argc,
                  char *argv[]);

struct option longopts[] = {
  { "instance", required_argument, 0, 'i' },
  { "output", required_argument, 0, 'o' },
  { "solver", required_argument, 0, 's' },
  { "verbose", no_argument, 0, 'v' },
  { "help", no_argument, 0, 'h' },
  { 0, 0, 0, 0 },
};
const std::string DEFAULT_OUTPUT_FILE = "./result.txt";
const std::string DEFAULT_SOLVER_NAME = "PIBT";


int main(int argc, char *argv[]) {
  std::string instance_file = "";
  std::string output_file = DEFAULT_OUTPUT_FILE;
  std::string solver_name = DEFAULT_SOLVER_NAME;

  // command line args
  int opt, longindex;
  opterr = 0;  // ignore getopt error
  while ((opt = getopt_long(argc, argv, "i:o:s:vh",
                            longopts, &longindex)) != -1) {
    switch (opt) {
    case 'i':
      instance_file = std::string(optarg);
      break;
    case 'o':
      output_file = std::string(optarg);
      break;
    case 's':
      solver_name = std::string(optarg);
      break;
    case 'v':
      VERVOSE = true;
      Solver::setVerbose(true);
      break;
    case 'h':
      printHelp();
      return 0;
    default:
      break;
    }
  }

  if (instance_file.length() == 0) {
    std::cout << "specify instance file using -i [INSTANCE-FILE], e.g.,"
              << std::endl;
    std::cout << "> ./app -i ../instance/sample.txt" << std::endl;
    return 0;
  }

  // set problem
  Problem* P = new Problem(instance_file);

  // solve
  Solver* solver = getSolver(solver_name, P, argc, argv);
  solver->solve();

  // output result
  solver->makeLog(output_file);
  info("save result as ", output_file);

  return 0;
}

Solver* getSolver(const std::string solver_name,
                  Problem* P,
                  int argc,
                  char *argv[])
{
  Solver* solver;
  if (solver_name == "PIBT") {
    solver = new PIBT(P);
  } else {
    warn("unknown solver name, continue by PIBT");
    solver = new PIBT(P);
  }
  solver->setParams(argc, argv);
  return solver;
}

void printHelp() {
  std::cout << "\nUsage: ./app [OPTIONS]\n"
            << "\n**instance file is necessary to run MAPF simulator**\n\n"
            << "  -i --instance [INSTANCE-FILE] instance file path\n"
            << "  -s --solver [SOLVER_NAME]     solver\n"
            << "  -o --output [OUTPUT-FILE]     ouptut file path\n"
            << "  -v --verbose                  print additional info\n"
            << "  -h --help                     help\n"
            << "\nSolver Options:"
            << std::endl;
  // each solver
  PIBT::printHelp();
}
