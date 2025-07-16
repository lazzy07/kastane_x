#pragma once

#include <cstdint>

namespace KX{
  namespace Comp{
    struct CompiledFluent{
      std::uint64_t id;
      bool m_Value;
    };
  }
}