#pragma once

#include <cstdint>
#include <string>

namespace KX{
  namespace Logic{
    struct Object{
      std::uint64_t id;
      std::size_t type;
      std::string m_Name;
    };
  }
}