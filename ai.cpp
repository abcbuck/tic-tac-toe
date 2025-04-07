#include "ai.h"

#include "game-logic.h"

#include <random>
#include <unordered_map>

//Transposition table definitions
enum ApproximationType {EXACT, LOWERBOUND, UPPERBOUND};
struct TranspositionTableEntry {
  bool isValid = false;
  ApproximationType flag;
  int value;
};
std::unordered_map<short, TranspositionTableEntry> transpositionTable; //short is board state, the transpositionTable is always cleared at the end of its usage (after every game)

//using 1 for win, 0 for draw, -1 for loss
int negamax(short node, int alpha, int beta, std::string &lastMove) {
  int originalAlpha = alpha;

  if(transpositionTable[node].isValid) {
    switch(transpositionTable[node].flag) {
      case EXACT:
      return transpositionTable[node].value;

      case LOWERBOUND:
      if(transpositionTable[node].value > alpha)
        alpha = transpositionTable[node].value;
      break;

      case UPPERBOUND:
      if(transpositionTable[node].value < beta)
        beta = transpositionTable[node].value;
    }
    if(alpha >= beta)
      return transpositionTable[node].value;
  }

  //check if node is terminal, i.e. contains a won or drawn game
  if(lastMove != "") { //calls of negamax from other functions always have lastMove == "" to indicate the node to be searched isn't terminal
    int fs = fieldSum(node);
    if(fs>6) { //two moves have been played by each player, so it is theoretically possible a player wins now
      if(isWon(node, lastMove))
        return -1; //the player who chose the last move wins, so the player whose turn it is loses
      else if(fs>12) //the game is drawn, as one player has played more than four moves (so nine moves have been played), and none of the players has won
        return 0;
    }
  }

  std::forward_list<std::string> moves = generateMoves(node);
  int value = std::numeric_limits<int>::min();
  for(auto& move : moves) {
    short childNode = makeMove(node, move);
    value = std::max(value, -negamax(childNode, -beta, -alpha, move));
    if(value >= beta) //alpha-beta cutoff
      break;
    if(value > alpha)
      alpha = value;
  }

  TranspositionTableEntry newEntry;
  newEntry.value = value;
  if(value <= originalAlpha)
    newEntry.flag = UPPERBOUND;
  else if(value >= beta)
    newEntry.flag = LOWERBOUND;
  else
    newEntry.flag = EXACT;
  newEntry.isValid = true;
  transpositionTable[node] = newEntry;

  return value;
}

std::string getAIMove(short boardState) {
  std::forward_list<std::string> moves = generateMoves(boardState);
  int bestValue = std::numeric_limits<int>::min();
  std::vector<std::string> bestMoves;
  for(auto& move : moves) {
    short childNode = makeMove(boardState, move);
    int value = -negamax(childNode, -std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), move);
    if(value == bestValue) {
      bestMoves.push_back(move);
    }
    else if(value > bestValue) {
      bestValue = value;
      bestMoves.clear();
      bestMoves.push_back(move);
    }
  }
  //return a random move from the set of best moves
  static std::mt19937_64 RNG;
  std::uniform_int_distribution<int> randomMoveNumber(0, static_cast<int>(bestMoves.size())-1);
  return bestMoves[randomMoveNumber(RNG)];
}
