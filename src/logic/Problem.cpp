#include "Problem.hpp"
#include <iostream>


KX::Logic::Problem::Problem(std::string name, std::vector<Object> objects, std::vector<Action> actions): m_Name(name), m_Objects(objects), m_Actions(actions)
{
  std::cout << "Problem: " + name + " created!" << std::endl;
}
