#include "loadmenu.h"

#include "../player/ingamemenu.h"
#include <nds.h>
#include "../../exception.h"

LoadMenu::LoadMenu(Game &game)
    : serializer(game)
{
  currentStep = 0;
  currentStepName = "Loading Sky";
  serializer.openRead("minicraft.dat");
}

void LoadMenu::tick(Game &game)
{
  int levelSize = 128;

  switch (currentStep)
  {
  case -1:
      currentStepName = "Error. Press A or B.";
      if (game.justTapped(KEY_A) || game.justTapped(KEY_B))
      {
        close(game);
      }
    return;
  case 0:
    game.frameSkipEnabled = false;
    game.levels.clear();

    serializer.loadFromFile_EmplaceBack_Serialized<Level>(game.levels);
    if (serializer.hasError())
    {
      currentStep = -1;
      return;
    }
    if (game.levels.back().player)
    {
      game.player = game.levels.back().player;
      game.currentLevel = 0;
    }

    currentStepName = "Loading Overworld";
    break;
  case 1:
    serializer.loadFromFile_EmplaceBack_Serialized<Level>(game.levels);
    if (serializer.hasError())
    {
      currentStep = -1;
      return;
    }
    if (game.levels.back().player)
    {
      game.player = game.levels.back().player;
      game.currentLevel = 1;
    }

    currentStepName = "Loading Underground 1";
    break;
  case 2:
    serializer.loadFromFile_EmplaceBack_Serialized<Level>(game.levels);
    if (serializer.hasError())
    {
      currentStep = -1;
      return;
    }
    if (game.levels.back().player)
    {
      game.player = game.levels.back().player;
      game.currentLevel = 2;
    }

    currentStepName = "Loading Underground 2";
    break;
  case 3:
    serializer.loadFromFile_EmplaceBack_Serialized<Level>(game.levels);
    if (serializer.hasError())
    {
      currentStep = -1;
      return;
    }
    if (game.levels.back().player)
    {
      game.player = game.levels.back().player;
      game.currentLevel = 3;
    }

    currentStepName = "Loading Underground 3";
    break;
  case 4:
    serializer.loadFromFile_EmplaceBack_Serialized<Level>(game.levels);
    if (serializer.hasError())
    {
      currentStep = -1;
      return;
    }
    if (game.levels.back().player)
    {
      game.player = game.levels.back().player;
      game.currentLevel = 4;
    }

    currentStepName = "Initalizing Entities...";
    break;
  case 5:
    for (auto &level : game.levels)
    {
      level.initAfterLoad(game);
    }
    currentStepName = "Done!";
    break;
  case 6:
    serializer.close();
    game.frameSkipEnabled = true;
    game.setMenu(std::make_unique<InGameMenu>(game.player, game.levels[game.currentLevel].map));
    break;
  }

  currentStep++;
}

void LoadMenu::render(Screen &screen, Screen &bottomScreen)
{
  screen.clear(0);

  screen.renderTextCentered(currentStepName, screen.w / 2, screen.h / 2 - 16, Color::get(-1, 555, 555, 555));

  const int totalSteps = 7;

  int barX = screen.w / 2 - totalSteps * 4;
  int barY = screen.h / 2 + 16;

  screen.renderBoxFilled(barX, barY, totalSteps * 8, 8, Color::get(555));

  if (currentStep > 0)
    screen.renderBoxFilled(barX, barY, currentStep * 8, 8, Color::get(151));
}
