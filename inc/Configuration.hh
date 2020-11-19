#pragma once

#include "Set4LibInterfaces.hpp"
#include "Scene.hh"
//TO DO: hermetyzacja, metody libconfig i mobileobjectConfig
class Configuration
{

public:
  Set4LibInterfaces &libinterfaces;
  Scene &scene;
  Configuration(Set4LibInterfaces &rLibinterfaces, Scene &rScene);
  //Configuration() = default;
};

Configuration::Configuration(Set4LibInterfaces &rLibinterfaces, Scene &rScene)
    : libinterfaces(rLibinterfaces),
      scene(rScene)
{
}
