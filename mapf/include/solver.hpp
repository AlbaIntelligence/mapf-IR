#pragma once
#include <getopt.h>

#include <chrono>
#include <functional>
#include <queue>
#include <unordered_map>

#include "default_params.hpp"
#include "graph.hpp"
#include "paths.hpp"
#include "plan.hpp"
#include "problem.hpp"
#include "lib_solver.hpp"
#include "util.hpp"

class Solver
{
protected:
  std::string solver_name;

  Problem* P;
  Graph* G;
  std::mt19937* MT;

  // limitations
  const int max_timestep;
  const int max_comp_time;

  Time::time_point t_start;  // when to start solving

  Plan solution;     // solution
  double comp_time;  // time for deliberation
  bool solved;       // success -> true, failed -> false (default)

  bool verbose;      // true -> print additional info

  int LB_soc;       // lower bound of soc
  int LB_makespan;  // lower bound of makespan

  std::vector<std::vector<int>> DistanceTable;  // distance table [agent][node_id]
  std::vector<std::vector<int>>* DistanceTable_p;

  void createDistanceTable();  // preprocessing

public:
  // use search of original graph
  Path getPath(Node* const s, Node* const g) const { return G->getPath(s, g); }
  int pathDist(Node* const s, Node* const g) const { return G->pathDist(s, g); }

  // space-time A*
  Path getTimedPath(Node* const s,  // start
                    Node* const g,  // goal
                    AstarHeuristics& fValue,
                    CompareAstarNode& compare,
                    CheckAstarFin& checkAstarFin,
                    CheckInvalidAstarNode& checkInvalidAstarNode);

  Path getPrioritizedPath
  (const int id,  // agent id
   Node* const s,  // initial location
   Node* const g,  // goal location
   const Paths& paths,  // already reserved paths
   const int time_limit=-1,  // time limit
   const int upper_bound=-1,  // upper bound of timesteps
   const std::vector<std::tuple<Node*, int>>& constraints={},  // additional constraints, space-time
   CompareAstarNode& compare=compareAstarNodeBasic);

  Path getPrioritizedPath
  (const int id,
   const Paths& paths,
   const int time_limit=-1,
   const int upper_bound=-1,
   const std::vector<std::tuple<Node*, int>>& constraints={},
   CompareAstarNode& compare=compareAstarNodeBasic);

  int getSolverElapsedTime() const;  // get elapsed time from start
  int getRemainedTime() const;  // get remained time
  bool overCompTime() const;            // check time limit

  // print debug info (only when verbose=true)
  void info() const
  {
    if (verbose) std::cout << std::endl;
  }
  template <class Head, class... Tail>
  void info(Head&& head, Tail&&... tail) const
  {
    if (!verbose) return;
    std::cout << head << " ";
    info(std::forward<Tail>(tail)...);
  }

protected:
  // main
  virtual void run() {}

  // for log
  void makeLogBasicInfo(std::ofstream& log);
  void makeLogSolution(std::ofstream& log);

private:
  void start();
  void end();

  void computeLowerBounds();

public:
  Solver(Problem* _P);
  virtual ~Solver();

  // call start -> run -> end
  void solve();

  // getter
  Plan getSolution() const { return solution; };
  bool succeed() const { return solved; };
  std::string getSolverName() { return solver_name; };
  Problem* getP() { return P; }

  // get path distance for a_i
  int pathDist(const int i) const;
  int pathDist(const int i, Node* const s) const;

  int getLowerBoundSOC();
  int getLowerBoundMakespan();

  void setDistanceTable(std::vector<std::vector<int>>* p) { DistanceTable_p = p; }

  // for parameters
  virtual void setParams(int argc, char* argv[]){};
  void setVerbose(bool _verbose) { verbose = _verbose; }

  // show result
  void printResult();

  // for log
  virtual void makeLog(const std::string& logfile = "./result.txt");
};
