#include "game.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

int main() {
  Game Tanks;
  Tanks.Init();
  Tanks.Start();
  Tanks.UpdateScreen();
}
