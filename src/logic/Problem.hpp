#pragma once
#include <vector>

#include "Action.hpp"
#include "MaskedState.hpp"

namespace KX {
  namespace Logic{
    class Problem{
      public:
        Problem(std::string name, std::vector<Object> objects, std::vector<Action> actions);

        [[nodiscard]] const std::vector<Action>& getActions() const noexcept {return m_Actions;};
        [[nodiscard]] const std::vector<Object>& getObjects() const noexcept {return m_Objects;};
      private:
        std::string m_Name;
        std::vector<Object> m_Objects;
        std::vector<Action> m_Actions;
    };
  };
};