#pragma once
#ifndef MONSTER_H
#define MONSTER_H

#include "Character.h"
#include <string>

class Player;

class Monster : public Character
{
public:
	Monster();
	Monster(string name, int type);
	~Monster();
	int AttackPlayer(Player* playertoAttack, bool special);
	int Value;
	bool GetUsedSpcAttck()
	{
		return UsedSpcAttck;
	}
private:
	//this is not wanted to be edited outside of the class
	bool UsedSpcAttck;
};

#endif
