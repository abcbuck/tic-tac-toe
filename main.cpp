#include "game-logic.h"
#include "ui.h"

#include <iostream>

int main() {
  for(;;) {
    std::string gameMode = mainMenu();
    if (gameMode == "1") {
      playGame(true); // Single-player mode
    } else
    if (gameMode == "2") {
      playGame(false); // Two-player mode
    } else
    if(gameMode == "m" || gameMode == "M") {
      manual();
    } else
    if(gameMode == "q" || gameMode == "Q")
      return 0;
  }
}
