#include "Board.h"
#include "Side.h"

Board::Board(int nHoles, int nInitialBeansPerHole)
{
	if (nHoles <= 0)		// Checking for legality & making legal
		nHoles = 1;
	if (nInitialBeansPerHole < 0)
		nInitialBeansPerHole = 0;

	m_holes = nHoles;

	holeNorth = new Hole[nHoles + 1];		// Creating dynamic arrays to serve as holes in board, putting in beans & assigning numbers
	holeSouth = new Hole[nHoles + 1];
	for (int i = 0; i < nHoles + 1; i++)
	{
		holeNorth[i].m_beans = nInitialBeansPerHole;
		holeNorth[i].m_number = i;
		holeNorth[i].m_side = NORTH;

		holeSouth[i].m_beans = nInitialBeansPerHole;
		holeSouth[i].m_number = i + 1;
		holeSouth[i].m_side = SOUTH;
	}
	holeNorth[0].m_beans = 0;			// Set initial values of beans in pots to 0
	holeSouth[m_holes].m_beans = 0;
	holeSouth[m_holes].m_number = 0;
}

Board::Board(const Board & b)
{
	m_holes = b.holes();

	holeNorth = new Hole[m_holes + 1];		// Creating dynamic arrays to serve as holes in board, putting in beans & assigning numbers
	holeSouth = new Hole[m_holes + 1];
	for (int i = 0; i <= m_holes; i++)		// Copy information from each hole
	{
		holeNorth[i].m_beans = b.holeNorth[i].m_beans;
		holeNorth[i].m_number = b.holeNorth[i].m_number;
		holeNorth[i].m_side = NORTH;

		holeSouth[i].m_beans = b.holeSouth[i].m_beans;
		holeSouth[i].m_number = b.holeSouth[i].m_number;
		holeSouth[i].m_side = SOUTH;
	}
}

int Board::holes() const		// =Good=
{
	return m_holes;
}

int Board::beans(Side s, int hole) const		// =Good=
{
	if ((hole < 0) || (hole > m_holes))		// If illegal return -1
		return -1;

	if (s == NORTH)
		return holeNorth[hole].m_beans;	// North
	if ((s == SOUTH) && (hole == 0))
		return holeSouth[m_holes].m_beans;	// South Pot
	else
		return holeSouth[hole - 1].m_beans;	// South

	return -1;
}

int Board::beansInPlay(Side s) const		// =Good=
{
	int counter = 0;
	for (int i = 1; i <= m_holes; i++)
		counter += beans(s, i);
	return counter;
}

int Board::totalBeans() const		// =Good=
{
	int counter = 0;
	for (int i = 0; i <= m_holes; i++)
	{
		counter += beans(NORTH, i);
		counter += beans(SOUTH, i);
	}
	return counter;
}

bool Board::sow(Side s, int hole, Side & endSide, int & endHole)	// =Good=
{
	if ((hole <= 0) || (hole > m_holes))		// Check legality
		return false;
	if (beans(s, hole) == 0)
		return false;

	int beansHeld = beans(s, hole);			// Initialize and give value to beans held in hand, remove beans from hole, advance hand to first hole
	if (s == NORTH)
	{
		holeNorth[hole].m_beans = 0;
		hand = &holeNorth[hole - 1];
	}
	if (s == SOUTH)
	{
		holeSouth[hole - 1].m_beans = 0;
		hand = &holeSouth[hole];
	}

	Side playerSide = s;
	while (beansHeld != 0)
	{
		if (s == SOUTH)		// Hand South
		{
			if (hand->m_number == 0)	// If pot
			{
				if (playerSide == SOUTH)	// Place bean if your side
				{
					hand->m_beans += 1;
					beansHeld--;
					endHole = hand->m_number;
					endSide = SOUTH;
				}
				hand = &holeNorth[m_holes];		// Move to other side
				s = NORTH;
				continue;
			}
			hand->m_beans += 1;		// Place bean in hole
			beansHeld--;
			endHole = hand->m_number;
			endSide = SOUTH;
			hand++;
			continue;
		}
		if (s == NORTH)		// Hand North
		{
			if (hand->m_number == 0)	// If pot
			{
				if (playerSide == NORTH)	// Place bean if your side
				{
					hand->m_beans += 1;
					beansHeld--;
					endHole = hand->m_number;
					endSide = NORTH;
				}
				hand = &holeSouth[0];		// Move to other side
				s = SOUTH;
				continue;
			}
			hand->m_beans += 1;		// Place bean in hole
			beansHeld--;
			endHole = hand->m_number;
			endSide = NORTH;
			hand--;
			continue;
		}
	}
	return true;
}

bool Board::moveToPot(Side s, int hole, Side potOwner)		// =Good=
{
	if ((hole <= 0) || (hole > m_holes))	// Check legality
		return false;

	if (s == NORTH)	
	{
		if (potOwner == NORTH)	// Move North to North
		{
			holeNorth[0].m_beans += beans(NORTH, hole);
			holeNorth[hole].m_beans = 0;
		}
		else
		{
			holeSouth[m_holes].m_beans += beans(NORTH, hole);	// Move North to South
			holeNorth[hole].m_beans = 0;
		}
		return true;
	}
	else
	{
		if (potOwner == NORTH)
		{
			holeNorth[0].m_beans += beans(SOUTH, hole);	// Move South to North
			holeSouth[hole - 1].m_beans = 0;
		}
		else
		{
			holeSouth[m_holes].m_beans += beans(SOUTH, hole);	// Move South to South
			holeSouth[hole - 1].m_beans = 0;
		}
		return true;
	}
	return false;
}

bool Board::setBeans(Side s, int hole, int beans)		// =Good=
{
	if ((hole < 0) || (hole > m_holes) || (beans < 0))	// Check legality
		return false;

	if (s == NORTH)		// North side set
	{
		holeNorth[hole].m_beans = beans;
		return true;
	}
	else				// South side set
	{
		if (hole != 0)
			holeSouth[hole - 1].m_beans = beans;
		else
			holeSouth[m_holes].m_beans = beans;
		return true;
	}
	return false;
}