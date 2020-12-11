/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"

class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

TEST(PiezasTest, checkEmptyBoard) //checks that after creation of a board, the board is empty
{
  Piezas board;
	ASSERT_EQ(board.pieceAt(1,1), ' ');
}

TEST(PiezasTest, incorrectPlacement)//tests that an incorrect placement results in an Invalid return
{
  Piezas board;
	ASSERT_EQ(board.dropPiece(6), '?');
}

TEST(PiezasTest, negativePlacement) //makes sure that placing a piece in a negative area does not allow placement
{
  Piezas board;
	ASSERT_EQ(board.dropPiece(-3), '?');
}

TEST(PiezasTest, correctPlacement) //test that a placed piece is correctly received
{
  Piezas board;
  board.dropPiece(2);
	ASSERT_EQ(board.pieceAt(0,2), 'X');
}

TEST(PiezasTest, checkNoOverride)//check that placing a piece on a full column does not override top piece
{
  Piezas board;
  board.dropPiece(2);//x
	board.dropPiece(2);//o
	board.dropPiece(2);//x
	board.dropPiece(2);//o
	ASSERT_EQ(board.pieceAt(2,2), 'X');
}

TEST(PiezasTest, checkTurnFunction) //check that the turns are properly rotating
{
  Piezas board;
  board.dropPiece(2);
  board.dropPiece(2);
	ASSERT_EQ(board.pieceAt(1,2), 'O');
}

TEST(PiezasTest, checkMissedTurn)//check that the function properly skips a turn on a bad placement
{
  Piezas board;
  board.dropPiece(2);
  board.dropPiece(6);
  board.dropPiece(2);
	ASSERT_EQ(board.pieceAt(1,2), 'X');
}

TEST(PiezasTest, fullPlacement)//check that people are unable to place a piece on top of a full column
{
  Piezas board;
  board.dropPiece(2);
  board.dropPiece(2);
  board.dropPiece(2);
	ASSERT_EQ(board.dropPiece(2), ' ');
}

TEST(PiezasTest, resetFunction)//check that the reset function properly resets the board
{
  Piezas board;
  board.dropPiece(2);
  board.reset();
	ASSERT_EQ(board.pieceAt(0,2), ' ');
}

TEST(PiezasTest, checkOnlyBoardReset) //check that even though the board is reset, that only the board is, and not turn order
{
  Piezas board;
  board.dropPiece(2);
  board.reset();
	board.dropPiece(2);
	ASSERT_EQ(board.pieceAt(0,2), 'O');
}

TEST(PiezasTest, checkUnfinished) //tests that when gameState is called early, it will return Invalid for unfinished
{
  Piezas board;
  board.dropPiece(2);
	ASSERT_EQ(board.gameState(), '?');
}

TEST(PiezasTest, xWin) //tests that in a proper game where X wins, the gamestate returns likewise
{
  Piezas board;
  board.dropPiece(0);//x
  board.dropPiece(0);//o
  board.dropPiece(1);//x
  board.dropPiece(0);//o
  board.dropPiece(2);//x
  board.dropPiece(2);//o
  board.dropPiece(3);//x
  board.dropPiece(2);//o
  board.dropPiece(1);//x
  board.dropPiece(3);//o
  board.dropPiece(1);//x
  board.dropPiece(3);//o
	ASSERT_EQ(board.gameState(), 'X');
}

TEST(PiezasTest, tie) //checks that in the event of a tie, the gameState function returns properly
{
  Piezas board;
  board.dropPiece(0);//x
  board.dropPiece(0);//o
  board.dropPiece(1);//x
  board.dropPiece(1);//o
  board.dropPiece(2);//x
  board.dropPiece(2);//o
  board.dropPiece(3);//x
  board.dropPiece(3);//o
  board.dropPiece(0);//x
  board.dropPiece(1);//o
  board.dropPiece(2);//x
  board.dropPiece(3);//o
	ASSERT_EQ(board.gameState(), ' ');
}
