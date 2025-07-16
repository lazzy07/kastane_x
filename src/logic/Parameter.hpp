#include <cstdint>
#include "Object.hpp"

namespace KX
{
  namespace Logic{
    struct Parameter{
      Parameter(std::size_t id, std::string name, Object* object): id(id), m_Name(name), m_Object(object){}; // TODO:: Add the functionality for the values as well
      std::size_t id;
      Object* m_Object;
      std::string m_Name;
    };
  }
}
