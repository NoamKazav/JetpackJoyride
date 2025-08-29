#pragma once
#include <map>
#include <string>
#include <memory>
#include <utility> 

template <typename Base, typename... Args>
class GameFactory {
public:
    using Creator = std::unique_ptr<Base>(*)(Args&&...);
    static std::unique_ptr<Base> create(const std::string& name, Args&&... args) {
        auto it = getMap().find(name);
        if (it == getMap().end())
            return nullptr;
        return it->second(std::forward<Args>(args)...);
    }

    static bool registerit(const std::string& name, Creator func) {
        getMap().emplace(name, func);
        return true;
    }

private:
    static std::map<std::string, Creator>& getMap() {
        static std::map<std::string, Creator> map;
        return map;
    }
};
