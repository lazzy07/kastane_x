#include <vector>
#include "../logic/Problem.hpp"
#include "CompiledAction.hpp"
#include "../logic/Conjunction.hpp"
#include "CompiledState.hpp"

namespace KX{
  namespace Comp{
    class CompiledProblem{
      public:
        CompiledProblem(CompiledState initialState, CompiledState goalState);

      private:
        CompiledState m_GoalState;
        CompiledState m_InitialState;
        
        KX::Logic::Problem m_Problem;

        std::vector<CompiledAction> m_CompiledActions;
        std::vector<CompiledFluent> m_CompiledFluents;
        std::vector<CompiledState> m_States;
    };
  }
}