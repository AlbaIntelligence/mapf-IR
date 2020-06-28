/*
 * Implementation of Improved Conflict-based Search (ICBS)
 * for Iterative Refinement
 */

#pragma once
#include "icbs.hpp"
#include "solver_refine.hpp"

class ICBS_REFINE : public ICBS, SolverRefine {
private:
  CBS::CompareHighLevelNodes getObjective();
  void setInitialHighLevelNode(HighLevelNode* n);
  void invoke(HighLevelNode* h_node, int id);
  Path getInitialPath(int id);

public:
  ICBS_REFINE(Problem* _P,
              const Plan& _old_plan,
              const std::vector<int>& _sample);
  ~ICBS_REFINE() {};
};
