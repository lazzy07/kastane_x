#pragma once
#include <vector>
#include <unordered_map>
#include "Action.hpp"
#include "Entity.hpp"

namespace KX {
  namespace Logic{
    class Problem{
      public:
        Problem(std::string name);

        ObjectType* CreateObjectType(std::string name, ObjectType* parent = nullptr);
        Entity* CreateEntity(std::string name, ObjectType* objectType);
        Action* CreateAction(std::string name, std::vector<ObjectType*> parameterTypes);

        [[nodiscard]] const std::string& getName() const noexcept {return m_Name; };
        [[nodiscard]] const std::unordered_map<std::string, Action>& getActions() const noexcept {return m_Actions;};
        [[nodiscard]] const std::unordered_map<std::string, ObjectType>& getObjectTypes() const noexcept {return m_ObjectTypes;};
      private:
        std::string m_Name;
        std::unordered_map<std::string, ObjectType> m_ObjectTypes;
        std::unordered_map<std::string, Action> m_Actions;
        std::unordered_map<std::string, Entity> m_Entities;
    };
  };
};