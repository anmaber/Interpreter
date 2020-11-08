#pragma once

#include <map>
#include <string>
#include <memory>
#include "LibInterface.hh"

class Set4LibInterfaces 
{
private:
    std::map<std::string, std::shared_ptr<LibInterface>> set4LibInterfaces;
public:
    Set4LibInterfaces();
    std::shared_ptr<LibInterface> findInterface(const std::string& libName);
    ~Set4LibInterfaces();
};

Set4LibInterfaces::Set4LibInterfaces()
{
    set4LibInterfaces.insert({"Set", std::make_shared<LibInterface>("Set")});
    set4LibInterfaces.insert({"Move", std::make_shared<LibInterface>("Move")});
    set4LibInterfaces.insert({"Pause", std::make_shared<LibInterface>("Pause")});
    set4LibInterfaces.insert({"Rotate", std::make_shared<LibInterface>("Rotate")});
}

std::shared_ptr<LibInterface> Set4LibInterfaces::findInterface(const std::string& libName)
{
    auto iter = set4LibInterfaces.find(libName);
    if (iter != set4LibInterfaces.end())
    {
        return iter->second;
    }
    
    return nullptr;
}

Set4LibInterfaces::~Set4LibInterfaces()
{
}
