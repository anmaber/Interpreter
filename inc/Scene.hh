#pragma once

#include "MobileObj.hh"
#include <map>
#include <memory>

class Scene
{
private:
    std::map<std::string,std::shared_ptr<MobileObj>> mobileObjects;
public:
    std::shared_ptr<MobileObj> findMobileObject(const std::string& objectName);
    void addMobileObject(const std::string& objectName);
    Scene(/* args */);
    ~Scene();
};

Scene::Scene(/* args */)
{
}

Scene::~Scene()
{
}

std::shared_ptr<MobileObj> Scene::findMobileObject(const std::string& objectName)
{
    auto iter = mobileObjects.find(objectName);
    if(iter != mobileObjects.end())
    {
        return iter->second;
    }
    return nullptr;
}

void Scene::addMobileObject(const std::string& objectName)
{
    if(!findMobileObject(objectName))
    {
        auto mobileObject = std::make_shared<MobileObj>();
        mobileObject->SetName(objectName);
        mobileObjects.insert({objectName, mobileObject});
    }
}