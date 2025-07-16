#include "BoxWorldTest.hpp"
#include "../compiler/ProblemCompiler.hpp"
#include <vector>

KX::Test::BoxWorldTest::BoxWorldTest() : Test("BoxWorld"), m_Problem("BoxWorld")
{
  
}

void KX::Test::BoxWorldTest::run()
{
  KX::Logic::Problem* problem = new Logic::Problem("BoxWorld");

  KX::Logic::ObjectType* object = problem->CreateObjectType("Object");
  KX::Logic::ObjectType* table = problem->CreateObjectType("Table", object);
  KX::Logic::ObjectType* box = problem->CreateObjectType("Box", object);

  std::vector<KX::Logic::ObjectType*> moveParams;
  moveParams.push_back(box);
  moveParams.push_back(object);
  moveParams.push_back(box);

  std::vector<KX::Logic::ObjectType*> moveToTableParams;
  moveToTableParams.push_back(box);
  moveToTableParams.push_back(table);

  problem->CreateAction("move", moveParams);
  problem->CreateAction("moveToTable", moveToTableParams);

  KX::Comp::CompiledState initialState;
  KX::Comp::CompiledState goalState;

  KX::Comp::ProblemCompiler::CompileProblem(problem, initialState, goalState);

  free(problem);
}