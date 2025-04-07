#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <string>
#include <forward_list>

void playGame(bool isSinglePlayer);
short makeMove(short boardState, std::string &move);
bool isValidMove(std::string &move, short boardState);
bool isWon(short boardState, std::string &lastMove);
int getField(short boardState, const char* field);
int playerToMove(short boardState);
int playerNotToMove(short boardState);
int fieldSum(short boardState);
std::string getRandomMove(short boardState);
std::forward_list<std::string> generateMoves(short boardState);

#endif
