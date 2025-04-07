#ifndef UI_H
#define UI_H

#include <string>

void showBoard(short boardState, char symbols[3]);
std::string getPlayerMove(short boardState, std::string *names);
std::string mainMenu();
void manual();
bool playAgain();

#endif
