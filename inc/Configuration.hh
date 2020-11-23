#pragma once

#include <vector>
#include <string>


struct sceneElementConfiguration
{
  std::string name;
  std::string size;
  std::string color;
};

class Configuration
{

public:
  std::vector<sceneElementConfiguration> sceneConfiguration{};
  std::vector<std::string> libsConfiguration{};
};
