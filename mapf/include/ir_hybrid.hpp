#pragma once
#include "ir.hpp"

class IR_HYBRID : public IR
{
public:
  static const std::string SOLVER_NAME;

private:
  void refinePlan();

public:
  IR_HYBRID(Problem* _P);

  static void printHelp();
};
