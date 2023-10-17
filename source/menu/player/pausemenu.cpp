#include "pausemenu.h"
#include "../main/titlemenu.h"

#include "ingamemenu.h"

std::vector<std::string> optionsPause = {"Resume", "Save", "Quit"};

PauseMenu::PauseMenu(Game &game)
    : serializer(game)
{
  saveStepName = "PAUSED";
}

void PauseMenu::tick(Game &game)
{
  if (isSaving)
  {
    save(game);
    return;
  }
  if (game.justTapped(KEY_START))
    close(game);

  if (game.justTapped(KEY_UP))
    selected--;
  if (game.justTapped(KEY_DOWN))
    selected++;

  int optionCount = optionsPause.size();

  if (selected < 0)
    selected = optionCount - 1;
  if (selected >= optionCount)
    selected = 0;

  if (!game.justTapped(KEY_A))
    return;

  switch(selected)
  {
    default:
      selected = 0;
    case 0:
      close(game);
      break;
    case 1:
      saveStep = 0;
      isSaving = true;
      break;
    case 2:
      game.setMenu(std::unique_ptr<TitleMenu>());
      break;
  }
}

void PauseMenu::save(Game &game)
{
  switch(saveStep)
  {
    case -1:
      saveStepName = "Saving Failed.";
      if (!serializer.isClosed())
        serializer.close();
      if (!game.justTapped(KEY_A))
      {
        isSaving = false;
        return;
      }
      return;
    case 0:
      saveStepName = "Saving Sky...";
      break;
    case 1:
      if (!serializer.openWrite("minicraft.dat"))
      {
        saveStep = -1;
        return;
      }
      game.levels[0].serialize(serializer);
      if (serializer.hasError())
      {
        saveStep = -1;
        return;
      }
      saveStepName = "Saving Overworld...";
      break;
    case 2:
      game.levels[1].serialize(serializer);
      if (serializer.hasError())
      {
        saveStep = -1;
        return;
      }
      saveStepName = "Saving Underground 1...";
      break;
    case 3:
      game.levels[2].serialize(serializer);
      if (serializer.hasError())
      {
        saveStep = -1;
        return;
      }
      saveStepName = "Saving Underground 2...";
      break;
    case 4:
      game.levels[3].serialize(serializer);
      if (serializer.hasError())
      {
        saveStep = -1;
        return;
      }
      saveStepName = "Saving Underground 3...";
      break;
    case 5:
      game.levels[4].serialize(serializer);
      if (serializer.hasError())
      {
        saveStep = -1;
        return;
      }
      serializer.close();
      saveStepName = "Done!";
      break;
    case 6:
      if (!game.justTapped(KEY_A))
        return;
      isSaving = false;
      saveStepName = "PAUSED";
      return;
  }
  if (saveStep > -1)
    saveStep++;
}

void PauseMenu::render(Screen &screen, Screen &bottomScreen)
{
  int optionColor = Color::get(-1, 222, 222, 222);
  int highlightColor = Color::get(-1, 555, 555, 555);

  screen.renderTextCentered(saveStepName, screen.w / 2, 6 * 8, optionColor);

  for (size_t i = 0; i < optionsPause.size(); i++)
  {
    auto msg = optionsPause[i];

    int col = optionColor;
    if (i == selected)
    {
      msg = "> " + msg + " <";
      col = highlightColor;
    }
    screen.renderTextCentered(msg, screen.w / 2, (10 + i) * 8 + 4, col);
  }
}
