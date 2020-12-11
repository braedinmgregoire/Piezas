#include "Piezas.h"
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
  board.resize(BOARD_ROWS, std::vector<Piece>(BOARD_COLS));
  for(int i=0;i<BOARD_ROWS;i++){
    for(int j=0;j<BOARD_COLS;j++){
      board[i][j] = Blank;
    }
  }
  turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
  for(int i=0;i<BOARD_ROWS;i++){
    for(int j=0;j<BOARD_COLS;j++){
      board[i][j] = Blank;
    }
  }
  return;
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/
Piece Piezas::dropPiece(int column)
{
  Piece value;
  if(column < 0 || column >= BOARD_COLS){
    value = Invalid;
  }
  else if(board[BOARD_ROWS-1][column] != Blank){
    value = Blank;
  }
  else{
    int placeHeight = BOARD_ROWS-1;
    while(pieceAt(placeHeight-1,column) == Blank){
      placeHeight--;
    }
    board[placeHeight][column] = turn;
    value = pieceAt(placeHeight, column);
  }
  if(turn == O){
    turn = X;
  }
  else{
    turn = O;
  }
  return value;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
  if((row < 0 || row>=BOARD_ROWS) || (column < 0 || column >= BOARD_COLS)){
    return Invalid;
  }
  else{
    return board[row][column];
  }
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
  //check if game is over
  for(int i=0;i<BOARD_ROWS;i++){
    for(int j=0;j<BOARD_COLS;j++){
      if(board[i][j] == Blank){
        return Invalid;
      }
    }
  }
  int xMost = 0;
  int oMost = 0;
  //get x's points
  for(int i=0;i<BOARD_ROWS;i++){
    for(int j=0;j<BOARD_COLS;j++){
      if(board[i][j] == X){
        int xcount = 0;
        int xup = 0;
        int yup = 0;
        int ycount = 0;
        while(pieceAt(i,j+xup) == X){
          xcount++;
          xup++;
        }
        if(xcount > xMost){
          xMost = xcount;
        }
        while(pieceAt(i+yup,j) == X){
          ycount++;
          yup++;
        }
        if(ycount > xMost){
          xMost = ycount;
        }
      }
    }
  }
  //check board for largest o count
  for(int i=0;i<BOARD_ROWS;i++){
    for(int j=0;j<BOARD_COLS;j++){
      if(board[i][j] == O){
        int xcount = 0;
        int xup = 0;
        int yup = 0;
        int ycount = 0;
        while(pieceAt(i,j+xup) == O){
          xcount++;
          xup++;
        }
        if(xcount > oMost){
          oMost = xcount;
        }
        while(pieceAt(i+yup,j) == O){
          ycount++;
          yup++;
        }
        if(ycount > oMost){
          oMost = ycount;
        }
      }
    }
  }
  if(xMost > oMost){
    return X;
  }
  else if(oMost > xMost){
    return O;
  }
  else{
    return Blank;
  }
}
