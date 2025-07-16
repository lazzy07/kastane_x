#pragma once

#include "Test.hpp"
#include "../logic/Problem.hpp"

namespace KX{
  namespace Test {
    /**
     * This is the BoxWorld test (Does not test the compiler, but can be used to test the core planner [Does classical planning, not narrative planning])
     */
    class BoxWorldTest : Test {
      public:
        BoxWorldTest();
        virtual void run();

      private:
        KX::Logic::Problem m_Problem;
    };
  }
}