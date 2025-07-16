#pragma once

#include <string>
#include <vector>
#include "ObjectType.hpp"

namespace KX {
  namespace Logic{
    struct Action{
      Action(std::size_t id, std::string name): id(id), m_Name(name) {};
      std::size_t id;
      std::string m_Name;
      std::vector<ObjectType*> m_Parameters;
    };
  };
};