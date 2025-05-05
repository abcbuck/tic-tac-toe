#include "ui.h"

#include "game-logic.h"
#include "utility.h"

#include <iostream>
#include <print>

void showBoard(short boardState, char symbols[3]) {
  std::println("════╦═══╦═══╦═══╗");
  std::print("3   ║ {0}", symbols[boardState%3]);
  std::print(" ║ {0}", symbols[(boardState/=3)%3]);
  std::println(" ║ {0} ║", symbols[(boardState/=3)%3]);
  std::println("════╬═══╬═══╬═══╣");
  std::print("2   ║ {0}", symbols[(boardState/=3)%3]);
  std::print(" ║ {0}", symbols[(boardState/=3)%3]);
  std::println(" ║ {0} ║", symbols[(boardState/=3)%3]);
  std::println("════╬═══╬═══╬═══╣");
  std::print("1   ║ {0}", symbols[(boardState/=3)%3]);
  std::print(" ║ {0}", symbols[(boardState/=3)%3]);
  std::println(" ║ {0} ║", symbols[(boardState/=3)%3]);
  std::println("════╬═══╬═══╬═══╣");
  std::println("    ║   ║   ║   ║");
  std::println("    ║ A ║ B ║ C ║\n");
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
