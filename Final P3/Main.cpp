#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	BadPlayer bp1("Louie");
	HumanPlayer bp2("Vito");
	Board b(3, 1);
	Game g(b, &bp1, &bp2);
	g.play();
}


/*
#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

void doGameTests()
{
	BadPlayer bp1("Bart");
	BadPlayer bp2("Homer");
	Board b(3, 0);
	b.setBeans(SOUTH, 1, 2);
	b.setBeans(NORTH, 2, 1);
	b.setBeans(NORTH, 3, 2);
	Game g(b, &bp1, &bp2);
	bool over;
	bool hasWinner;
	Side winner;
	//    Homer
	//   0  1  2
	// 0         0
	//   2  0  0
	//    Bart
	g.status(over, hasWinner, winner);
	g.display();
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
		g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);

	g.move();
	//   0  1  0
	// 0         3
	//   0  1  0
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

	g.move();
	//   1  0  0
	// 0         3
	//   0  1  0
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

	g.move();
	//   1  0  0
	// 0         3
	//   0  0  1
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);

	g.move();
	//   0  0  0
	// 1         4
	//   0  0  0
	g.status(over, hasWinner, winner);
	assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
	assert(hasWinner && winner == SOUTH);
}

int main()
{
	doGameTests();
	cout << "Passed all tests" << endl;
}
*/
///=============================================================================================================================================
/*
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

void doPlayerTests()
{
	HumanPlayer hp("Marge");
	assert(hp.name() == "Marge"  &&  hp.isInteractive());
	BadPlayer bp("Homer");
	assert(bp.name() == "Homer" && !bp.isInteractive());
	SmartPlayer sp("Lisa");
	assert(sp.name() == "Lisa" && !sp.isInteractive());
	Board b(3, 2);
	b.setBeans(SOUTH, 2, 0);
	cout << "=========" << endl;
	int n = hp.chooseMove(b, SOUTH);
	cout << "=========" << endl;
	assert(n == 1 || n == 3);
	n = bp.chooseMove(b, SOUTH);
	assert(n == 1 || n == 3);
	n = sp.chooseMove(b, SOUTH);
	assert(n == 1 || n == 3);
}

int main()
{
	doPlayerTests();
	cout << "Passed all tests" << endl;
}
*/
///=============================================================================================================================================
/*
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;


void doBoardTests()
{
	Board b(3, 2);
	assert(b.holes() == 3 && b.totalBeans() == 12 &&
		b.beans(SOUTH, POT) == 0 && b.beansInPlay(SOUTH) == 6);
	b.setBeans(SOUTH, 1, 1);
	b.moveToPot(SOUTH, 2, SOUTH);
	assert(b.totalBeans() == 11 && b.beans(SOUTH, 1) == 1 &&
		b.beans(SOUTH, 2) == 0 && b.beans(SOUTH, POT) == 2 &&
		b.beansInPlay(SOUTH) == 3);
	Side es;
	int eh;
	b.sow(SOUTH, 3, es, eh);
	assert(es == NORTH && eh == 3 && b.beans(SOUTH, 3) == 0 &&
		b.beans(NORTH, 3) == 3 && b.beans(SOUTH, POT) == 3 &&
		b.beansInPlay(SOUTH) == 1 && b.beansInPlay(NORTH) == 7);
}

int main()
{
	doBoardTests();
	cout << "Passed all tests" << endl;
} */
///=============================================================================================================================================
/*
#include "Board.h"
#include "Player.h"
#include "Game.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{

	// ============================================Testing Board===================================================
	Board b(5, 5);
	cout << b.beansInPlay(NORTH) << endl;
	cout << b.totalBeans() << endl;
	Side s;
	int d;
	assert(b.holes() == 5);
	assert(b.beans(NORTH, 1) == 5);
	assert(b.totalBeans() == 50);
	assert(b.beansInPlay(NORTH) == 25);
	b.sow(NORTH, 3, s, d);
	for (int i = 0; i <= b.holes(); i++)
	{
		cout << b.beans(NORTH, i) << " ";
	}
	cout << endl;
	for (int i = 0; i <= b.holes(); i++)
	{
		cout << b.beans(SOUTH, i) << " ";
	}


	cout << endl << endl;
	b.setBeans(NORTH, 3, 10);
	cout << b.beansInPlay(NORTH) << endl;
	cout << b.totalBeans() << endl;
	for (int i = 0; i <= b.holes(); i++)
	{
		cout << b.beans(NORTH, i) << " ";
	}
	cout << endl;
	for (int i = 0; i <= b.holes(); i++)
	{
		cout << b.beans(SOUTH, i) << " ";
	}

	cout << endl << endl;
	b.sow(NORTH, 3, s, d);
	cout << b.beansInPlay(NORTH) << endl;
	cout << b.totalBeans() << endl;
	for (int i = 0; i <= b.holes(); i++)
	{
		cout << b.beans(NORTH, i) << " ";
	}
	cout << endl;
	for (int i = 0; i <= b.holes(); i++)
	{
		cout << b.beans(SOUTH, i) << " ";
	}

	cout << endl << endl;
	b.sow(SOUTH, 5, s, d);
	assert(b.beans(SOUTH, 5) == 0);
	cout << b.beansInPlay(SOUTH) << endl;
	cout << b.totalBeans() << endl;
	for (int i = 0; i <= b.holes(); i++)
	{
		cout << b.beans(NORTH, i) << " ";
	}
	cout << endl;
	for (int i = 0; i <= b.holes(); i++)
	{
		cout << b.beans(SOUTH, i) << " ";
	}

	return 0;
}
*/