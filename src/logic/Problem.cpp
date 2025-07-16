#include "Problem.hpp"
#include <iostream>


KX::Logic::Problem::Problem(std::string name): m_Name(name)
{
  std::cout << "Problem: " + name + " created!" << std::endl;
}

KX::Logic::ObjectType* KX::Logic::Problem::CreateObjectType(std::string name, ObjectType* parent)
{
  std::size_t id = m_ObjectTypes.size();
  ObjectType type = ObjectType(id, name, parent);
  m_ObjectTypes.insert({name, type});

  std::cout << "Type: " + name + " with ID: " + std::to_string(id) << " created!" << std::endl;

  return &m_ObjectTypes.at(name);
}

KX::Logic::Entity* KX::Logic::Problem::CreateEntity(std::string name, ObjectType *objectType)
{
  std::size_t id = m_Entities.size();
  Entity entity = Entity(id, objectType, name);
  m_Entities.insert({name, entity});

  std::cout << "Entity: " + name + " with ID: " + std::to_string(id) << " created!" << std::endl;

  return &m_Entities.at(name);
}

KX::Logic::Action* KX::Logic::Problem::CreateAction(std::string name, std::vector<ObjectType*> parameterTypes)
{
  std::size_t id = m_Actions.size();
  Action action = Action(id, name);
  
  for(ObjectType* param : parameterTypes){
    action.m_Parameters.push_back(param);
  }

  std::cout << "Action: " + action.m_Name + " with ID: " + std::to_string(action.id) + " created!" << std::endl;

  m_Actions.insert({name, action});
  return &m_Actions.at(name);
}
