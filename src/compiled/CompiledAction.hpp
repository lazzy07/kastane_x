#include <cstdint>
#include <vector>
#include "../logic/Action.hpp"
#include "CompiledFluent.hpp"

namespace KX{
  namespace Comp{
    struct CompiledAction{
      std::uint64_t id;
      Logic::Action* m_Action;
      std::vector<Logic::ObjectType*> m_Parameters;
      std::vector<CompiledFluent*> m_AddList; //List of CompiledFluentIDs in the add list
      std::vector<CompiledFluent*> m_DeleteList; //List of CompiledFluentIDs in the delete list
    };
  }
}