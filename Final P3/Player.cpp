#include "Player.h"
#include <iostream>

Player::Player(std::string name)	// Good
{
	m_name = name;
}

std::string Player::name() const	// Good
{
	return m_name;
}

bool Player::isInteractive() const	// Good
{
	return false;
}

int Player::chooseMove(const Board & b, Side s) const	// Good?
{
	return -1;
}

Player::~Player()	// Good?
{
	
}

//================================================== Human ======================================================
HumanPlayer::HumanPlayer(std::string name) : Player(name)	// =Good=
{ }


bool HumanPlayer::isInteractive() const		// Good
{
	return true;
}

int HumanPlayer::chooseMove(const Board & b, Side s) const		// Good
{
	if ((b.beansInPlay(s) == 0) || (b.beansInPlay(opponent(s)) == 0))	// If one player has no valid moves
		return -1;

	bool legal = false;
	int desired;				// Take in player input
	std::cout << "Pick a hole: ";
	std::cin >> desired;
	std::cout << std::endl;
	if ((b.beans(s, desired) > 0) && (desired > 0) && (desired <= b.holes()))	// If legal, skip loop
		legal = true;
	while (!legal)				// Loop until legal
	{
		std::cout << "Please pick another valid hole whose bean count is not zero: ";
		std::cin >> desired;
		if ((b.beans(s, desired) > 0) && (desired > 0) && (desired <= b.holes()))
			break;
	}
	return desired;
}

HumanPlayer::~HumanPlayer()		// Good?
{
}

//================================================== Bad Player ======================================================
BadPlayer::BadPlayer(std::string name) : Player(name)		// =Good=
{ }


bool BadPlayer::isInteractive() const		// Good
{
	return false;
}

int BadPlayer::chooseMove(const Board & b, Side s) const	// Good
{
	if ((b.beansInPlay(s) == 0) || (b.beansInPlay(opponent(s)) == 0))	// If one player has no valid moves
		return -1;
	
	int i = 1;
	while (i <= b.holes())		// Select first legal move to the left
	{
		if (b.beans(s, i) != 0)
			break;
		i++;
	}
	if (i == b.holes() + 1)
		return -1;

	return i;
}

BadPlayer::~BadPlayer()		// Good?
{
}

//================================================== Smart Player ======================================================
SmartPlayer::SmartPlayer(std::string name) : Player(name)	// =Good=
{ }


bool SmartPlayer::isInteractive() const		// Good
{
	return false;
}

int SmartPlayer::chooseMove(const Board & b, Side s) const		// TO-DO
{
	if ((b.beansInPlay(s) == 0) || (b.beansInPlay(opponent(s)) == 0))	// If one player has no valid moves
		return -1;

	int i = 1;
	while (i <= b.holes())		// Select first legal move to the left
	{
		if (b.beans(s, i) != 0)
			break;
		i++;
	}
	if (i == b.holes() + 1)
		return -1;

	return i;
}

SmartPlayer::~SmartPlayer()		// Good
{
}
