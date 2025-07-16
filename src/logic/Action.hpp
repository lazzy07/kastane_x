#pragma once

#include <string>
#include <vector>

#include "Parameter.hpp"

namespace KX {
  namespace Logic{
    struct Action{
      std::size_t id;
      std::string m_Name;
      std::vector<Parameter> m_Parameters;
    };
  };
};