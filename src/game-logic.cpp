#include "game-logic.h"

#include "ai.h"
#include "ui.h"

#include <cmath>
#include <cstring>

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <string>

#include <forward_list>
#include <vector>

void playGame(bool isSinglePlayer) {
  std::string names[3];
  char symbols[3];

  names[0] = "Emptiness";
  symbols[0] = ' ';
  
  const std::string computerName = "Computer";
  if (isSinglePlayer) {
    names[2] = computerName;

    std::cout << "Please enter your name: ";
    singlePlayerNameInput:
    std::cin >> names[1];
    if (names[1]==names[2]) {
      std::cout << "Please don't take the computer's name: ";
      goto singlePlayerNameInput;
    }
    char input[3];
    std::cout << "Please enter your symbol: ";
    singlePlayerSymbolInput:
    std::cin >> std::setw(3) >> input;
    if (std::strlen(input)>1) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "Please enter only one character: ";
      goto singlePlayerSymbolInput;
    }
    symbols[1] = input[0];
    symbols[2] = symbols[1]!='X'?'X':'O';
  } else {
    // Two-player setup
    //No name or symbol checking. Equal names and symbols are allowed as a feature.
    for (int i=1; i<=2; i++) {
      std::cout << "Player " << i << ", please enter your name: ";
      std::cin >> names[i];
      char input[3];
      std::cout << "Player " << i << ", please enter your symbol: ";
      twoPlayerSymbolInput:
      std::cin >> std::setw(3) >> input;
      if (std::strlen(input)>1) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Please enter only one character: ";
        goto twoPlayerSymbolInput;
      }
      symbols[i] = input[0];
    }
  }

  std::cout << std::endl;

  const std::string cancelGameString = "q";
  for (;;) {
    short boardState = 0;
    bool stillPlaying = true;
    while (stillPlaying) {
      //OnLeavingScope([]() { transpositionTable.clear(); }); //We can use the same table for the next game, so this isn't needed.

      showBoard(boardState, symbols);

      std::string move;
      if (isSinglePlayer && names[playerToMove(boardState)]==computerName) {
        move = getAIMove(boardState);
        std::cout << computerName << " plays " << move << "." << std::endl;
      } else {
        do {
          move = getPlayerMove(boardState, names);
          if (move==cancelGameString) {
            std::cout << std::endl;
            return;
          }
        } while (!isValidMove(move, boardState));
      }

      boardState = makeMove(boardState, move);

      const int fs = fieldSum(boardState);
      if (fs>6) { //two moves have been played by each player, so it is theoretically possible a player wins now
        if (isWon(boardState, move)) {
          stillPlaying = false;

          showBoard(boardState, symbols);
          std::cout << names[3-playerToMove(boardState)] << " has won! :)" << std::endl
                    << std::endl;

          if (!playAgain())
            return;
        } else if (fs>12) { //the game is drawn, as one player has played more than four moves (so nine moves have been played), and none of the players has won
          stillPlaying = false;

          showBoard(boardState, symbols);
          std::cout << "The game ends in a draw." << std::endl
                    << std::endl;

          if (!playAgain())
            return;
        }
      }
      //player changes automatically every round
    }

    //When playing again, instead of changing players, exchange their data, not to mess with our field sum invariants
    std::swap(names[1], names[2]);
    std::swap(symbols[1], symbols[2]);
  }
}

short makeMove(short boardState, std::string &move) {
  return boardState + static_cast<short>(std::pow(3, (3*('3'-move[1])+move[0]-'a')))*playerToMove(boardState);
}

bool isValidMove(std::string &move, short boardState) {
  if(!(move.length()==2 && move[0] >= 'a' && move[0] <= 'c' && move[1] >= '1' && move[1] <= '3')) {
    std::cerr << "Please enter a move with the valid format, e.g. 'a1' or 'c2'." << std::endl;
    return false;
  }
  if(getField(boardState, move.c_str()) != 0) {
    std::cerr << "Please enter coordinates of an empty field, e.g. '" << getRandomMove(boardState) << "'." << std::endl;
    return false;
  }
  return true;
}

bool isWon(short boardState, std::string &lastMove) {
  auto boardField = std::bind(&getField, boardState, std::placeholders::_1); //for easier writing on the next lines
  //only check rows, columns and diagonals where the last move was played
  return (lastMove[0] == 'a' &&                                                             //columns
           boardField("a1") == boardField("a2") && boardField("a2") == boardField("a3")) ||
         (lastMove[0] == 'b' &&
           boardField("b1") == boardField("b2") && boardField("b2") == boardField("b3")) ||
         (lastMove[0] == 'c' &&
           boardField("c1") == boardField("c2") && boardField("c2") == boardField("c3")) ||

         (lastMove[0]-'a' == lastMove[1]-'1' &&                                             //diagonals
           boardField("a1") == boardField("b2") && boardField("b2") == boardField("c3")) ||
         (lastMove[0]-'a' == '3'-lastMove[1] &&
           boardField("c1") == boardField("b2") && boardField("b2") == boardField("a3")) ||

         (lastMove[1] == '3' && ( boardState      %=27)!=0 && boardState%13==0) || //a highly inefficient yet effective way to check the rows
         (lastMove[1] == '2' && ((boardState/= 27)%=27)!=0 && boardState%13==0) ||
         (lastMove[1] == '1' && ((boardState/=729)%=27)!=0 && boardState%13==0);
}

int getField(short boardState, const char* field) {
  return boardState/static_cast<short>(std::pow(3, (3*('3'-field[1])+field[0]-'a')))%3;
}

int playerToMove(short boardState) {
  return fieldSum(boardState)%3+1;
}

int playerNotToMove(short boardState) {
  return 2-fieldSum(boardState)%3;
}

int fieldSum(short boardState) {
  int ret = boardState%3;
  while((boardState/=3)>0)
    ret += boardState%3;
  return ret;
}

std::string getRandomMove(short boardState) {
  std::forward_list<std::string> moveList = generateMoves(boardState);
  std::vector<std::string> moveVector;
  while(!moveList.empty()) {
    moveVector.push_back(moveList.front());
    moveList.pop_front();
  }
  //return a random move from the set of moves
  std::default_random_engine RNG;
  std::uniform_int_distribution<int> randomMoveNumber(0, static_cast<int>(moveVector.size())-1);
  return moveVector[randomMoveNumber(RNG)];
}

std::forward_list<std::string> generateMoves(short boardState) {
  std::forward_list<std::string> moves;
  for(int i=0; i<9; i++, boardState/=3) {
    if(boardState%3 == 0) {
      std::string move;
      move.append(1, 'a'+i%3);
      move.append(1, '3'-i/3);
      moves.push_front(move);
    }
  }
  return moves;
}
