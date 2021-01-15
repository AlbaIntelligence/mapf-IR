#include "../include/solver.hpp"

#include <fstream>

#include "../include/lib_cbs.hpp"

Solver::Solver(Problem* _P)
    : P(_P),
      G(_P->getG()),
      MT(_P->getMT()),
      max_timestep(P->getMaxTimestep()),
      max_comp_time(P->getMaxCompTime()),
      LB_soc(0),
      LB_makespan(0)
{
  solved = false;
  verbose = false;

  // for solvers using MDD
  LibCBS::MDD::MT = MT;
}

void Solver::solve()
{
  start();
  run();
  end();
}

Path Solver::getTimedPath
(Node* const s,
 Node* const g,
 AstarHeuristics& fValue,
 CompareAstarNode& compare,
 CheckAstarFin& checkAstarFin,
 CheckInvalidAstarNode& checkInvalidAstarNode)
{
  return getPathBySpaceTimeAstar
    (s, g, fValue, compare, checkAstarFin, checkInvalidAstarNode, getRemainedTime());
}

void Solver::start()
{
  info("  start solving MAPF by", solver_name);
  t_start = std::chrono::system_clock::now();
}

// failed & solution is empty -> add solution the initial configuration
void Solver::end()
{
  comp_time = getSolverElapsedTime();
  info("  finish, elapsed=", comp_time);
  if (!solved && solution.empty()) solution.add(P->getConfigStart());
}

int Solver::getSolverElapsedTime() const { return getElapsedTime(t_start); }
int Solver::getRemainedTime() const { return max_comp_time - getSolverElapsedTime(); }

bool Solver::overCompTime() const
{
  return getSolverElapsedTime() >= max_comp_time;
}

void Solver::computeLowerBounds()
{
  LB_soc = 0;
  LB_makespan = 0;

  for (int i = 0; i < P->getNum(); ++i) {
    int d = pathDist(i);
    LB_soc += d;
    if (d > LB_makespan) LB_makespan = d;
  }
}

int Solver::getLowerBoundSOC()
{
  if (LB_soc == 0) computeLowerBounds();
  return LB_soc;
}

int Solver::getLowerBoundMakespan()
{
  if (LB_makespan == 0) computeLowerBounds();
  return LB_makespan;
}

void Solver::printResult()
{
  std::cout << "solved=" << solved << ", solver=" << std::right << std::setw(8)
            << solver_name << ", comp_time(ms)=" << std::right << std::setw(8)
            << comp_time << ", soc=" << std::right << std::setw(6)
            << solution.getSOC() << " (LB=" << std::right << std::setw(6)
            << LB_soc << ")"
            << ", makespan=" << std::right << std::setw(4)
            << solution.getMakespan() << " (LB=" << std::right << std::setw(6)
            << LB_makespan << ")" << std::endl;
}

void Solver::makeLog(const std::string& logfile)
{
  std::ofstream log;
  log.open(logfile, std::ios::out);
  makeLogBasicInfo(log);
  makeLogSolution(log);
  log.close();
}

void Solver::makeLogBasicInfo(std::ofstream& log)
{
  Grid* grid = reinterpret_cast<Grid*>(P->getG());
  log << "instance=" << P->getInstanceFileName() << "\n";
  log << "agents=" << P->getNum() << "\n";
  log << "map_file=" << grid->getMapFileName() << "\n";
  log << "solver=" << solver_name << "\n";
  log << "solved=" << solved << "\n";
  log << "soc=" << solution.getSOC() << "\n";
  log << "makespan=" << solution.getMakespan() << "\n";
  log << "comp_time=" << comp_time << "\n";
}

void Solver::makeLogSolution(std::ofstream& log)
{
  log << "starts=";
  for (int i = 0; i < P->getNum(); ++i) {
    Node* v = P->getStart(i);
    log << "(" << v->pos.x << "," << v->pos.y << "),";
  }
  log << "\ngoals=";
  for (int i = 0; i < P->getNum(); ++i) {
    Node* v = P->getGoal(i);
    log << "(" << v->pos.x << "," << v->pos.y << "),";
  }
  log << "\n";
  log << "solution=\n";
  for (int t = 0; t <= solution.getMakespan(); ++t) {
    log << t << ":";
    auto c = solution.get(t);
    for (auto v : c) {
      log << "(" << v->pos.x << "," << v->pos.y << "),";
    }
    log << "\n";
  }
}
