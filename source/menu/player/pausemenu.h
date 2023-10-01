#pragma once

#include "../menu.h"

class PauseMenu : public Menu
{
  Serializer serializer;
  char selected = 0;
  signed char saveStep = 0;
  std::string saveStepName;
  bool isSaving = false;

  void save(Game &game);
public:
  PauseMenu(Game &game);

  void tick(Game &game) override;
  void render(Screen &screen, Screen &bottomScreen) override;
};
