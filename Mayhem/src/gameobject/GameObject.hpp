#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H 

#include <iostream>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

#include "components/Transform.hpp"
#include "components/Component.hpp"

#include "../math/MathUtils.hpp"
#include "../util/MayhemUtil.hpp"

namespace Mayhem {
    namespace ECS {
        class GameObject {
            private:
                std::unordered_map<std::type_index, Components::Component*> components;
                std::string name;
                Utils::UUID uuid;
            public:
                Components::Transform* transform = new Components::Transform(Math::Vector3f(), Math::Vector3f());

                enum STATE {
                    MOUSEHOVER,
                    SELECTED,
                    DEFAULT,
                };

                STATE state = STATE::DEFAULT;
                    
                GameObject(std::string name);
                GameObject(std::string name, Components::Transform transform);

                std::unordered_map<std::type_index, Components::Component*> GetComponents();
 
                template <typename T>
                T* GetComponent() {
                    if (!HasComponent<T>()) {return nullptr;}

                    return static_cast<T*>(components.at(typeid(T)));
                }

                template <typename T>
                void AddComponent(T component) {
                    if (HasComponent<T>()) {return;}
                    components[typeid(component)] = new T(component);
                    static_cast<T*>(components.at(typeid(component)))->gameObject = this;
                }

                template <typename T>
                void RemoveComponent() {
                    if (HasComponent<T>() && typeid(T) != typeid(Components::Transform)) {
                        delete components.at(typeid(T));
                        components.erase(typeid(T));
                    }
                }

                template <typename T>
                bool HasComponent() {
                    for (auto& co : components) {
                        if (co.first == typeid(T)) {
                            return true;
                        }
                    }

                    return false;
                }

                std::string getName() { return this->name; }
                Utils::UUID getID() { return this->uuid; }
        };
    }
}

#endif /* ifndef GAMEOBJECT_H */
