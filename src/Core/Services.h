#ifndef SERVICES_H
#define SERVICES_H

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <stdexcept>
#include <string>

namespace GameCore
{
    class Services
    {
    public:
        template<class T>
        void set(std::shared_ptr<T> ptr)
        {
            _map[typeid(T)] = ptr;
        }

        template<class T>
        std::shared_ptr<T> get() const {
            auto it = _map.find(typeid(T));
            if (it == _map.end()) throw std::runtime_error("Service not found");
            return std::static_pointer_cast<T>(it->second);
        }

        template<class T>
        bool has() const {
            return _map.count(typeid(T)) > 0;
        }

    private:
        std::unordered_map<std::type_index, std::shared_ptr<void>> _map;
    };

}

#endif