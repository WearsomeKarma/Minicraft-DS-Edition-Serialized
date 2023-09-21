#pragma once

#include <string>

class ToolDetails
{
public:
  static ToolDetails shovel;
  static ToolDetails hoe;
  static ToolDetails sword;
  static ToolDetails pickaxe;
  static ToolDetails axe;

  const std::string name;
  const int sprite;

private:
  ToolDetails(std::string name, int sprite) : name(name), sprite(sprite) {}
};
