#include "Test.hpp"
#include <iostream>

KX::Test::Test::Test(std::string name) : m_Name(name)
{
  std::cout << "Test: " + m_Name + " started!" << std::endl;
}