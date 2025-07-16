#pragma once
#include <cstdint>
#include "ObjectType.hpp"

namespace KX{
  namespace Logic{
    struct Entity{
      Entity(std::size_t id, ObjectType* type, std::string name): id(id), m_Type(type), m_Name(name){};
      std::size_t id;
      ObjectType* m_Type;
      std::string m_Name;
    };
  }
}