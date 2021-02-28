
#pragma warning(disable: 4786)

#include <typeinfo.h>

using namespace std;

#include "Sprite.h"


#ifndef SPACESHIP_H
#define SPACESHIP_H


class SpaceShip
{
public:

	// Constructors and destructors.
	SpaceShip();
	~SpaceShip();


	// Member variables.
	int m_x;
	int m_y;

	Sprite m_Sprite;
};

#endif