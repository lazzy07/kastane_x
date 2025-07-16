#pragma once
#include "../logic/Problem.hpp"
#include "../compiled/CompiledProblem.hpp"

namespace KX{
  namespace Comp{
    class ProblemCompiler{
      public:
        static CompiledProblem* CompileProblem(KX::Logic::Problem* problem, CompiledState initialState, CompiledState goalState);
    };
  }
}