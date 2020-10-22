#include "Game.h"
#include <iostream>
using namespace std;

Game::Game(const Board & b, Player * south, Player * north)		// =Good=
{
	board = new Board(b);
	s = south;
	n = north;
	whosturn = SOUTH;
}

void Game::display() const		// =Good=
{
	cout << n->name() << endl << "   ";			// North name
	if (board->beans(NORTH, 0) > 9)
		cout << " ";
	for (int i = 1; i <= board->holes(); i++)		// North holes
		cout << board->beans(NORTH, i) << "   ";
	cout << endl << board->beans(NORTH, 0) << "     ";	// Pot values
	for (int i = 1; i <= board->holes() - 1; i++)
		cout << "    ";
	cout << board->beans(SOUTH, 0) << endl << "   ";
	if (board->beans(NORTH, 0) > 9)
		cout << " ";
	for (int i = 1; i <= board->holes(); i++)		// South holes
		cout << board->beans(SOUTH, i) << "   ";
	cout << endl << s->name() << endl << endl;			// South name
	if (!isOver)
	{
		cout << "It is ";
		if (whosturn == 0)							// Whose turn is it
			cout << n->name() << "'s turn." << endl << endl;
		else
			cout << s->name() << "'s turn." << endl << endl;
	}
}

void Game::status(bool & over, bool & hasWinner, Side & winner) const	// =Good=
{
	if ((board->beansInPlay(NORTH) != 0) && (board->beansInPlay(SOUTH) != 0))	// Moves still possible
		over = false;
	else
	{
		over = true;
		for (int i = 1; i <= board->holes(); i++)	// Move all the holes to their appropriate pot
		{
			board->moveToPot(NORTH, i, NORTH);
			board->moveToPot(SOUTH, i, SOUTH);
		}
		if (board->beans(NORTH, 0) > board->beans(SOUTH, 0))	// Set appropriate winner
		{
			hasWinner = true;
			winner = NORTH;
		}
		else if (board->beans(NORTH, 0) < board->beans(SOUTH, 0))	// In the case of a tie
		{
			hasWinner = true;
			winner = SOUTH;
		}
		else
			hasWinner = false;
	}
}

bool Game::move()
{
	status(isOver, hasWinner, winner);
	if (isOver)
		return false;
	else
	{
		bool currentPlay = true;
		Side endSide;
		int endHole;
		while (currentPlay)
		{
			if (whosturn == NORTH)		// If its north's turn
			{
				int hole = n->chooseMove(*board, NORTH);	// Take in a choice
				if (hole == -1)								// If no valid positions
				{
					status(isOver, hasWinner, winner);
					cout << "No valid moves available." << endl;
					return false;
				}
				board->sow(NORTH, hole, endSide, endHole);
				if (endSide == NORTH && endHole == 0)		// Get another turn if in pot
				{
					cout << "Nice job! Take another turn!" << endl << endl;
					display();
					continue;
				}
				if (endSide == NORTH && board->beans(NORTH, endHole) == 1)	// Capture
				{
					if (board->beans(SOUTH, endHole) != 0)
					{
						board->moveToPot(NORTH, endHole, NORTH);
						board->moveToPot(SOUTH, endHole, NORTH);
						cout << "Capture! Take the other player's beans!" << endl << endl;
					}
				}
				whosturn = SOUTH;
				display();
				return true;
			}

			if (whosturn == SOUTH)		// If its south's turn
			{
				int hole = s->chooseMove(*board, SOUTH);	// Take in a choice
				if (hole == -1)								// If no valid positions
				{
					status(isOver, hasWinner, winner);
					return false;
				}
				board->sow(SOUTH, hole, endSide, endHole);
				if (endSide == SOUTH && endHole == 0)		// Get another turn if in pot
				{
					cout << "Nice job! Take another turn!" << endl << endl;
					display();
					continue;
				}
				if (endSide == SOUTH && board->beans(SOUTH, endHole) == 1)	// Capture
				{
					if (board->beans(NORTH, endHole) != 0)
					{
						board->moveToPot(SOUTH, endHole, SOUTH);
						board->moveToPot(NORTH, endHole, SOUTH);
						display();
						cout << "Capture! Take the other player's beans!" << endl << endl;
					}
				}
				whosturn = NORTH;
				display();
				return true;
			}
		}
	}

}

void Game::play()
{
	status(isOver, hasWinner, winner);
	display();
	while (!isOver)		// Keep doing moves until game is over
	{
		move();
		status(isOver, hasWinner, winner);
		if (!(n->isInteractive()) && !(s->isInteractive()))		// Two bots, need prompt to continue
		{
			cout << "Press enter to continue..." << endl;
			cin.ignore();
		}
	}
	display();			// Game is over, display results
	if (hasWinner)
	{
		if (winner == NORTH)		// North wins
		{
			cout << "Congratulations! " << n->name() << " beat " << s->name() << " " << board->beans(NORTH, 0) << " to " << board->beans(SOUTH, 0) << "!" << endl;
		}
		if (winner == SOUTH)		// South wins
		{
			cout << "Congratulations! " << s->name() << " beat " << n->name() << " " << board->beans(SOUTH, 0) << " to " << board->beans(NORTH, 0) << "!" << endl;
		}
	}
	else							// Tie
	{
		cout << "It's a tie!" << endl;
	}
}

int Game::beans(Side s, int hole) const		// =Good=
{
	return board->beans(s, hole);
}
