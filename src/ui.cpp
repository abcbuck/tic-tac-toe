#include "ui.h"

#include "game-logic.h"
#include "utility.h"

#include <iostream>

void showBoard(short boardState, char symbols[3]) {
  /*
  ════╦═══╦═══╦═══╗
  3   ║   ║   ║   ║
  ════╬═══╬═══╬═══╣
  2   ║   ║ X ║ X ║
  ════╬═══╬═══╬═══╣
  1   ║ O ║   ║   ║
  ════╬═══╬═══╬═══╣
      ║   ║   ║   ║
      ║ A ║ B ║ C ║
  */
  //const char tl = static_cast<char>(201); //╔ top left
    const char tr = static_cast<char>(187); //╗ top right
  //const char br = static_cast<char>(188); //╝ bottom right
  //const char bl = static_cast<char>(200); //╚ bottom left
    const char  h = static_cast<char>(205); //═ horizontal
    const char  v = static_cast<char>(186); //║ vertical
    const char  t = static_cast<char>(203); //╦ top
    const char  r = static_cast<char>(185); //╣ right
  //const char  b = static_cast<char>(202); //╩ bottom
  //const char  l = static_cast<char>(204); //╠ left
    const char  m = static_cast<char>(206); //╬ middle
  
  //need to call std::cout multiple times to invoke the correct sequencing of changes to the boardState variable
  std::cout << h << h << h << h << t <<      h      <<      h      <<      h      << t <<      h      <<      h      <<      h      << t <<      h      <<      h      <<      h      << tr << std::endl
            <<      "3   "      << v <<  ' '  <<  symbols[boardState%3];
                                                              std::cout <<  ' '  << v <<  ' ' << symbols[(boardState/=3)%3];
                                                                                                                   std::cout << ' ' << v << ' ' <<  symbols[(boardState/=3)%3] << ' ' <<  v << std::endl;
  std::cout << h << h << h << h << m <<      h      <<      h      <<      h      << m <<      h      <<      h      <<      h      << m <<      h      <<      h      <<      h      <<  r << std::endl
            <<      "2   "      << v << ' ' <<  symbols[(boardState/=3)%3];
                                                                 std::cout << ' ' << v << ' ' <<  symbols[(boardState/=3)%3];
                                                                                                                   std::cout << ' ' << v << ' ' <<  symbols[(boardState/=3)%3] << ' ' <<  v << std::endl;
  std::cout << h << h << h << h << m <<      h      <<      h      <<      h      << m <<      h      <<      h      <<      h      << m <<      h      <<      h      <<      h      <<  r << std::endl
            <<      "1   "      << v << ' ' <<  symbols[(boardState/=3)%3];
                                                                 std::cout << ' ' << v << ' ' <<  symbols[(boardState/=3)%3];
                                                                                                                   std::cout << ' ' << v << ' ' <<  symbols[(boardState/=3)%3] << ' ' <<  v << std::endl
            << h << h << h << h << m <<      h      <<      h      <<      h      << m <<      h      <<      h      <<      h      << m <<      h      <<      h      <<      h      <<  r << std::endl
            <<      "    "      << v <<                   "   "                   << v <<                   "   "                   << v <<                   "   "                   <<  v << std::endl
            <<      "    "      << v <<                   " a "                   << v <<                   " b "                   << v <<                   " c "                   <<  v << std::endl
            << std::endl;
}

std::string getPlayerMove(short boardState, std::string *names) {
  std::cout << "It's your turn, " << names[playerToMove(boardState)] << ". Please enter your move (move format [abc][123]) or 'q' to cancel the game: ";
  std::string ret;
  std::cin >> ret;
  return ret;
}

std::string mainMenu() {
  std::cout << "Tic-tac-toe, programmed by Robin L. Buck" << std::endl
            << "Enter a key to continue:" << std::endl
            << "1: Single-player mode" << std::endl
            << "2: Two-player mode" << std::endl
            << "m: Manual" << std::endl
            << "q: Quit" << std::endl
            << std::endl
            << "> ";
  std::string ret;
  std::cin >> ret;
  std::cout << std::endl;
  return ret;
}

void manual() {
  std::cout << "Try to get three of your symbol in a row, column or diagonal to win." << std::endl
            << "Enter coordinates to place your symbol when it's your move." << std::endl
            << "Play against the computer or play against a friend locally." << std::endl
            << std::endl;
}

bool playAgain() {
  OnLeavingScope doThis([]() { std::cout << std::endl; });
  std::cout << "Do you want to play again? (y/n): ";
  std::string input;
  for(;;) {
    std::cin >> input;
    if(input == "y")
      return true;
    else if(input == "n")
      return false;
    std::cout << "Please enter 'y' or 'n': ";
  }
}
