#include <lib_ir.hpp>

#include "gtest/gtest.h"

TEST(LibIR, refineSinglePaths)
{
  Grid G("8x8.map");

  Node* v = G.getNode(0);
  Node* u = G.getNode(1);
  Node* w = G.getNode(2);
  Node* x = G.getNode(3);

  Config starts = { v, w };
  Config goals  = { u, x };

  Plan plan;
  plan.add(starts);
  plan.add({ v, x });
  plan.add(goals);
  ASSERT_TRUE(plan.validate(starts, goals));
  ASSERT_EQ(plan.getSOC(), 3);

  Plan refined_plan = LibIR::refineSinglePaths(plan, &G, starts, goals, 1000);
  ASSERT_TRUE(plan.validate(starts, goals));
  ASSERT_EQ(refined_plan.getSOC(), 2);
}

TEST(LibIR, refineTwoPathsAtGoal)
{
  Grid G("8x8.map");

  Node* a = G.getNode(0);
  Node* b = G.getNode(1);
  Node* c = G.getNode(2);
  Node* d = G.getNode(3);
  Node* e = G.getNode(4);
  Node* x = G.getNode(3, 1);

  Config starts = { c, a };
  Config goals  = { d, e };
  Plan plan;
  plan.add({ c, a });
  plan.add({ d, b });
  plan.add({ d, c });
  plan.add({ x, d });
  plan.add({ d, e });
  ASSERT_TRUE(plan.validate(starts, goals));
  ASSERT_EQ(plan.getSOC(), 8);
  ASSERT_EQ(plan.getMakespan(), 4);

  Plan refined_plan = LibIR::refineTwoPathsAtGoal(plan, &G, starts, goals, 1000);
  ASSERT_TRUE(refined_plan.validate(starts, goals));
  ASSERT_EQ(refined_plan.getSOC(), 7);
  ASSERT_EQ(refined_plan.getMakespan(), 6);
}

TEST(LibIR, refineTwoPathsAtGoal_challenging)
{
  Grid G("8x8.map");

  Node* a = G.getNode(0);
  Node* b = G.getNode(1);
  Node* c = G.getNode(2);
  Node* d = G.getNode(3);
  Node* e = G.getNode(4);
  Node* f = G.getNode(5);
  Node* g = G.getNode(6);
  Node* h = G.getNode(7);
  Node* x = G.getNode(6, 1);
  Node* y = G.getNode(7, 1);

  Config starts = { f, d, a };
  Config goals  = { g, y, x };
  Plan plan;
  plan.add({ f, d, a });
  plan.add({ g, e, b });
  plan.add({ g, f, c });
  plan.add({ x, g, d });
  plan.add({ g, h, e });
  plan.add({ g, y, f });
  plan.add({ h, y, g });
  plan.add({ g, y, x });
  ASSERT_TRUE(plan.validate(starts, goals));
  ASSERT_EQ(plan.getSOC(), 19);
  ASSERT_EQ(plan.getMakespan(), 7);

  Plan refined_plan = LibIR::refineTwoPathsAtGoal(plan, &G, starts, goals, 1000);
  ASSERT_TRUE(refined_plan.validate(starts, goals));
  ASSERT_EQ(refined_plan.getSOC(), 13);
  ASSERT_EQ(refined_plan.getMakespan(), 7);
}
