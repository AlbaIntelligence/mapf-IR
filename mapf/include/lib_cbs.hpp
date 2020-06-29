#pragma once
#include "solver.hpp"

namespace LibCBS {
  // ======================================
  // conflict
  struct Constraint;
  using Constraint_p = std::shared_ptr<Constraint>;
  using Constraints = std::vector<Constraint_p>;

  // ======================================
  // MDD
  struct MDDNode;
  using MDDNodes = std::vector<MDDNode*>;
  struct MDD;
  using MDD_p = std::shared_ptr<MDD>;
  using MDDs = std::vector<MDD_p>;


  // ======================================
  // conflict
  struct Constraint {
    int id;   // agent id, -1 -> for all agetnts
    int t;    // at t
    Node* v;  // at t
    Node* u;  // used only for swap conflict, at t-1

    void println();
  };

  // for CBS-style solvers
  Constraints getFirstConstraints(const Paths& paths);

  // for ICBS
  Constraints getPrioritizedConflict(const Paths& paths,
                                     const MDDs& mdds);

  // ======================================
  // MDD
  struct MDDNode {
    int t;
    Node* v;
    MDDNodes next;
    MDDNodes prev;

    MDDNode(int _t, Node* _v);
    ~MDDNode();
    bool operator==(const MDDNode& other) const;
  };

  struct MDD {
    int c;  // cost
    int i;  // agent
    Graph* G;  // original graph
    Node* s;  // start
    Node* g;  // goal;
    std::vector<MDDNodes> body;  // t: 0...c
    bool valid;  // false -> no path from s to g
    MDDNodes GC;  // for memory management

    // MDD without any constraints
    static std::unordered_map<std::string, MDD_p> PURE_MDD_TABLE;

    MDD(int _c, int _i, Graph* _G, Node* _s, Node* _g, bool _valid);
    MDD(int _c, int _i, Problem* P, Constraints constraints);
    ~MDD();
    MDD(const MDD& other);  // copy

    MDDNode* createNewNode(int t, Node* v);
    void copy(const MDD& other);
    std::string getPureMDDName();
    void build();
    void update(const Constraints& _constraints);
    void deleteForward(MDDNode* node);
    void deleteBackword(MDDNode* node);
    Path getPathByDFS() const;
    Path getPath() const;
    Path getPath(Constraint_p const constraint) const;
    int getWidth(int t) const;
    void println() const;
  };
};
