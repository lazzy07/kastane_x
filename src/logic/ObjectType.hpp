#pragma once

#include <cstdint>
#include <string>

namespace KX{
  namespace Logic{
    struct ObjectType{
      ObjectType(std::size_t id, std::string name, ObjectType* parent = nullptr): id(id), m_Name(name), m_Parent(parent) {};
      std::size_t id;
      std::string m_Name;
      ObjectType* m_Parent;
    };
  }
}