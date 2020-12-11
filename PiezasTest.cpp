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

TEST(PiezasTest, checkEmptyBoard)
{
  Piezas board;
	ASSERT_EQ(board.pieceAt(1,1), ' ');
}

TEST(PiezasTest, incorrectPlacement)
{
  Piezas board;
	ASSERT_EQ(board.dropPiece(6), '?');
}

TEST(PiezasTest, negativePlacement)
{
  Piezas board;
	ASSERT_EQ(board.dropPiece(-3), '?');
}

TEST(PiezasTest, correctPlacement)
{
  Piezas board;
  board.dropPiece(2);
	ASSERT_EQ(board.pieceAt(0,2), 'X');
}

TEST(PiezasTest, checkTurnFunction)
{
  Piezas board;
  board.dropPiece(2);
  board.dropPiece(2);
	ASSERT_EQ(board.pieceAt(1,2), 'O');
}

TEST(PiezasTest, fullPlacement)
{
  Piezas board;
  board.dropPiece(2);
  board.dropPiece(2);
  board.dropPiece(2);
	ASSERT_EQ(board.dropPiece(2), ' ');
}

TEST(PiezasTest, resetFunction)
{
  Piezas board;
  board.dropPiece(2);
  board.reset();
	ASSERT_EQ(board.pieceAt(0,2), ' ');
}
