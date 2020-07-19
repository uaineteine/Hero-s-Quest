#pragma once

#include "Character.h"

class Item : public Character
{
public:
	Item();
	~Item();
	void SetType(int type);
	string Description;
	int GetCost()
	{
		return Cost;
	}
	bool IsConsumable()
	{
		return Consumable;
	}
private:
	//these are not wanted to be edited outside of the class
	int Type;
	int Cost;
	bool Consumable;
};

