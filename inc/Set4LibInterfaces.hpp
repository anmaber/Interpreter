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
    bool addInterface(const std::string& libname);
    ~Set4LibInterfaces();
};

Set4LibInterfaces::Set4LibInterfaces()
{}

std::shared_ptr<LibInterface> Set4LibInterfaces::findInterface(const std::string& libName)
{
    auto iter = set4LibInterfaces.find(libName);
    if (iter != set4LibInterfaces.end())
    {
        return iter->second;
    }
    
    return nullptr;
}

bool Set4LibInterfaces::addInterface(const std::string& libname)
{
    auto libInterface = std::make_shared<LibInterface>();
    if(!libInterface->initInterface(libname))
    {
        return false;
    }
    set4LibInterfaces.insert({libname, libInterface});
    return true;
}

Set4LibInterfaces::~Set4LibInterfaces()
{}
