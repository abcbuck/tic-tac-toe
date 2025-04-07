#ifndef AI_H
#define AI_H

#include <string>

int negamax(short node, int alpha, int beta, std::string &lastMove);
std::string getAIMove(short boardState);

#endif
