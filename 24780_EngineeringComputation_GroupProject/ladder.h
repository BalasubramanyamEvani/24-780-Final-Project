#ifndef LADDER_H_IS_INCLUDED
#define LADDER_H_IS_INCLUDED

#include "baseobject.h"

class Ladder : public BaseObject
{
public:
	int floor, windowHeight;

	Ladder();
	Ladder(int x, int floor, int windowHeight);
	~Ladder();

	void Rendar(void);
};

#endif
