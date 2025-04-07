# An overview of the code

We need to store and display the board, make moves, and check for a win after a move.

## The storage model

The board state is represented as a ternary number to fit two bytes
(9 ternary fields make for (3<sup>9</sup>=19683 < 2<sup>15</sup>-1=32767=`SHORT_MAX` < 2<sup>16</sup>=65536) two bytes of storage).
The player to move doesn't need to be stored explicitly. More on that later.
The sign bit is unused.

For ease of printing, the lowest trit (ternary equivalent of a trit) encodes the top left field of the board
with the other trits following in the order of regular English reading:
```
    0 1 2
    3 4 5
    6 7 8
```

Single digits of the ternary number represent single fields of the 3x3 tic-tac-toe board:
```
  0 = empty field
  1 = field marked by player 1
  2 = field marked by player 2
```

Example representation:

Player 1 marked `b2`, player 2 marked `a1`, then player 1 marked `c2`.

Board:
```
3   0 0 0
2   0 1 1
1   2 0 0

    a b c
```
Ternary number: 2110000\
Decimal number: 1\*3<sup>4</sup> + 1\*3<sup>5</sup> + 2\*3<sup>6</sup> = 1782\
Hexadecimal number: `0x06F6`

Functions to change or check the board state are defined mathematically.


## The program flow

```
Main menu
  Single player mode
  Two player mode
  Manual

Single player mode:
  choose player 1 name
  choose player 1 symbol
  play against the engine
  
Two player mode:
  choose player 1 name
  choose player 1 symbol
  choose player 2 name
  choose player 2 symbol
  play against each other

Play
  show board
  prompt for move input
    allow premature cancelling of the game
  check input validity
    reprompt in case of bad input
  from the third move, check for a win:
  if won
    play again (and change who begins) OR
    go back to main menu
  change player
  repeat
```


### The field sum

As players alternate, [the sum of the values of all fields modulo 3] alternates between 0 and 1 (as 1 and 2 are added for each move of player 1 and 2), allowing us to read whose turn it is.\
It also allows us to apply an additional win condition prior to normal checking (when 2 moves have been made by each player, the field sum is 6),
and to check for a draw (when the last move has been made, the field sum is higher than 12, as this value is reached when both players have made 4 moves each).


### AI

```
functions

  negamax
  generateMoves
  (transpositionTableLookup
  transpositionTableStore) //implemented as an unordered_map

TranspositionTableEntry data structure

  isValid //entry exists in transposition table
  flag //one of EXACT, LOWERBOUND, UPPERBOUND
  value
```
Check Wikipedia for an introduction to the methods used here (archived links):
- [Minimax algorithm](https://en.wikipedia.org/w/index.php?title=Minimax&oldid=1282084908#Combinatorial_game_theory)
- [Negamax algorithm](https://en.wikipedia.org/w/index.php?title=Negamax&oldid=1280991606)
- [Alpha-beta pruning](https://en.wikipedia.org/w/index.php?title=Alpha%E2%80%93beta_pruning&oldid=1283911367)
- [Transposition table](https://en.wikipedia.org/w/index.php?title=Transposition_table&oldid=1260263170)
