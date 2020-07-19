#include "stdafx.h"
#include "Item.h"


Item::Item()
{
}
Item::~Item()
{
}
void Item::SetType(int type)
{
	Type = type;
	Description = "";
	if (Type == 1)
	{
		Name = "Shield";
		SetStats(0, 0, 0, 1, 0);
		Description = "Adds 1 defence";
		Cost = 4;
	}
	if (Type == 2)
	{
		Name = "Breastplate";
		SetStats(0, 0, 0, 3, 0);
		Description = "Adds 2 defence";
		Cost = 6;
	}
	if (Type == 3)
	{
		Name = "Longsword";
		SetStats(0, 0, 2, 0, 0);
		Description = "Adds 2 attack";
		Cost = 6;
	}
	if (Type == 4)
	{
		Name = "Warhammer";
		SetStats(0, 0, 0, 0, 3);
		Description = "Adds 3 special attack";
		Cost = 6;
	}
	if (Type == 5)
	{
		Name = "Heart Jar";
		SetStats(4, 0, 0, 0, 0);
		Description = "Adds 4 max hit points";
		Cost = 4;
	}
	if (Type == 6)
	{
		Name = "Healing potion";
		SetStats(5, 0, 0, 0, 0);
		Cost = 2;
		Description = "Heals 5 hit points";
		Consumable = true;
	}
	if (Type == 7)
	{
		Name = "Poison";
		SetStats(0, 0, 0, 0, 2);
		Cost = 3;
		Description = "Adds 3 to special attack";
		Consumable = true;
	}
}