#pragma once
#include <functional>

#include "paths.hpp"
#include "plan.hpp"
#include "util.hpp"

// convert Plan to Paths
[[maybe_unused]] static Paths planToPaths(const Plan& plan)
{
  if (plan.empty()) halt("invalid operation.");
  int num_agents = plan.get(0).size();
  Paths paths(num_agents);
  int makespan = plan.getMakespan();
  for (int i = 0; i < num_agents; ++i) {
    Path path;
    for (int t = 0; t <= makespan; ++t) {
      path.push_back(plan.get(t, i));
    }
    paths.insert(i, path);
  }
  return paths;
}

// convert Paths to Plan
[[maybe_unused]] static Plan pathsToPlan(const Paths& paths)
{
  Plan plan;
  if (paths.empty()) return plan;
  int makespan = paths.getMakespan();
  int num_agents = paths.size();
  for (int t = 0; t <= makespan; ++t) {
    Config c;
    for (int i = 0; i < num_agents; ++i) {
      c.push_back(paths.get(i, t));
    }
    plan.add(c);
  }
  return plan;
}

/*
 * Template of Space-Time A*.
 * See the following reference.
 *
 * Cooperative Pathﬁnding.
 * D. Silver.
 * AI Game Programming Wisdom 3, pages 99–111, 2006.
 */
struct AstarNode {
  Node* v;
  int g;  // in getTimedPath, g represents t
  int f;
  AstarNode* p;  // parent
  std::string name;

  AstarNode(Node* _v, int _g, int _f, AstarNode* _p)
      : v(_v), g(_g), f(_f), p(_p), name(getName(_v, _g))
  {
  }

  static std::string getName(Node* _v, int _g)
  {
    return std::to_string(_v->id) + "-" + std::to_string(_g);
  }
};
using CompareAstarNode = std::function<bool(AstarNode*, AstarNode*)>;
using CheckAstarFin = std::function<bool(AstarNode*)>;
using CheckInvalidAstarNode = std::function<bool(AstarNode*)>;
using AstarHeuristics = std::function<int(AstarNode*)>;
using AstarNodes = std::vector<AstarNode*>;

[[maybe_unused]] static Path getPathBySpaceTimeAstar(
    Node* const s, Node* const g, AstarHeuristics& fValue,
    CompareAstarNode& compare, CheckAstarFin& checkAstarFin,
    CheckInvalidAstarNode& checkInvalidAstarNode, const int time_limit)
{
  auto t_start = Time::now();

  AstarNodes GC;  // garbage collection
  auto createNewNode = [&GC](Node* v, int g, int f, AstarNode* p) {
    AstarNode* new_node = new AstarNode(v, g, f, p);
    GC.push_back(new_node);
    return new_node;
  };

  // OPEN and CLOSE list
  std::priority_queue<AstarNode*, AstarNodes, CompareAstarNode> OPEN(compare);
  std::unordered_map<std::string, bool> CLOSE;

  // initial node
  AstarNode* n = createNewNode(s, 0, 0, nullptr);
  n->f = fValue(n);
  OPEN.push(n);

  // main loop
  bool invalid = true;
  while (!OPEN.empty()) {
    // check time limit
    if (time_limit > 0 && getElapsedTime(t_start) > time_limit) break;

    // minimum node
    n = OPEN.top();
    OPEN.pop();

    // check CLOSE list
    if (CLOSE.find(n->name) != CLOSE.end()) continue;
    CLOSE[n->name] = true;

    // check goal condition
    if (checkAstarFin(n)) {
      invalid = false;
      break;
    }

    // expand
    Nodes C = n->v->neighbor;
    C.push_back(n->v);
    for (auto u : C) {
      int g_cost = n->g + 1;
      AstarNode* m = createNewNode(u, g_cost, 0, n);
      m->f = fValue(m);
      // already searched?
      if (CLOSE.find(m->name) != CLOSE.end()) continue;
      // check constraints
      if (checkInvalidAstarNode(m)) continue;
      OPEN.push(m);
    }
  }

  Path path;
  if (!invalid) {  // success
    while (n != nullptr) {
      path.push_back(n->v);
      n = n->p;
    }
    std::reverse(path.begin(), path.end());
  }

  // free
  for (auto p : GC) delete p;

  return path;
}

[[maybe_unused]] static CompareAstarNode compareAstarNodeBasic =
    [](AstarNode* a, AstarNode* b) {
      if (a->f != b->f) return a->f > b->f;
      if (a->g != b->g) return a->g < b->g;
      return false;
    };
