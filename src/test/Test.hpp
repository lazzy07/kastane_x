#pragma once
#include <string>

/**
 * This is the generic test class
 */
namespace KX{
  namespace Test{
    class Test{
      public:
        Test(std::string name);
        virtual void run() = 0; //Runs the test
      private:
        std::string m_Name;
    };
  }
}