#include "CompiledFluent.hpp"
#include <cstdint>
#include <vector>

namespace KX{
  namespace Comp{
    struct CompiledState{
      std::uint64_t id;
      std::vector<CompiledFluent> m_Fluents;
    };
  }
}