
#pragma warning(disable: 4786)

#include <typeinfo.h>

using namespace std;

#include "stdafx.h"
#include <stdio.h>



#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


class GameObject
{
public:

	// Constructors and destructors.
	GameObject();
	~GameObject();


private:

	// Member variables.
	int m_x;			// offset from a GameRegion's left.
	int m_y;            // offset from a GameRegion's top.
	int m_ImageIndex;	// index into a GameMap sprite manager array.


};

#endif