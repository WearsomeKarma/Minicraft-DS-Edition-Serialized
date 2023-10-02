#pragma once

#include <string>

enum ToolItemKind
{
  TIK_UNKNOWN,
  TIK_Shovel,
  TIK_Hoe,
  TIK_Sword,
  TIK_Pickaxe,
  TIK_Axe,
};

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
  const enum ToolItemKind toolItemKind;

private:
  ToolDetails(std::string name, int sprite, enum ToolItemKind toolItemKind) 
      : name(name), sprite(sprite), toolItemKind(toolItemKind) 
  {}
};
