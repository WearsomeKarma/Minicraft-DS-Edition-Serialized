#pragma once

#include "../menu.h"
#include "../../serialization/serializer.h"

class LoadMenu : public Menu
{
private:
  std::string currentStepName;
  signed char currentStep;
  Serializer serializer;

public:
  LoadMenu(Game &game);

  void tick(Game &game) override;
  void render(Screen &screen, Screen &bottomScreen) override;
};
