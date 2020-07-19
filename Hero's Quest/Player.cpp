#include "stdafx.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include <algorithm>

//default constructor
Player::Player()
{
}
Player::Player(string name)
{
	//declare variables of player class
	Name = name;
	UsedSpcAttck = false;
	//minimum setting
	PrizeMoney = 0;
	Level = 1;
	SetStats(20, 20, 3, 3, 2);
	//debug SetStats(200, 200, 30, 30, 20);
}

Player::~Player()
{
}

//returns damage dealt from attack
int Player::AttackMonster(Monster* monsterToAttack, bool special)
{
	Monster TheMonster = *monsterToAttack;
	//1-6 bonus attack
	int attckBonus = (rand() % 6) + 1 + Buffs.Attack;
	if (special == true)
		attckBonus += StatusPoints.SpecialAttack + Buffs.SpecialAttack;

	if (UsedSpcAttck == false)
		UsedSpcAttck = special;

	//1-6 bonus defence for monster
	int defenceBonus = (rand() % 6) + 1;

	int difference = StatusPoints.Attack + attckBonus - 
		(defenceBonus + TheMonster.StatusPoints.Defence);
	if (difference > 0)
	{
		//take damage from monster
		TheMonster.StatusPoints.Health -= difference;
		//set variable back
		*monsterToAttack = TheMonster;
		return difference;
	}
	//no damage dealt-blocked
	else return 0;
}

void Player::ResetRound()
{
	StatusPoints.Health = StatusPoints.MaxHealth;
	UsedSpcAttck = false;
	Buffs.Attack = 0;
	Buffs.Defence = 0;
	Buffs.Health = 0;
	Buffs.MaxHealth = 0;
	Buffs.SpecialAttack = 0;
}
void Player::AddItem(Item itemToAdd)
{
	//add to vector
	PlayerItems.push_back(itemToAdd);
	//take away dosh
	PrizeMoney -= itemToAdd.GetCost();
	//Add attributes item possesses;
	StatusPoints.MaxHealth += itemToAdd.StatusPoints.Health;
	StatusPoints.Defence += itemToAdd.StatusPoints.Defence;
	StatusPoints.Attack += itemToAdd.StatusPoints.Attack;
	StatusPoints.SpecialAttack += itemToAdd.StatusPoints.SpecialAttack;
}
void Player::ConsumeItem(Item* itemToConsume)
{
	Item item = *itemToConsume;
	Buffs.Attack += item.StatusPoints.Attack;
	Buffs.Defence += item.StatusPoints.Defence;
	Buffs.Health += item.StatusPoints.Health;
	Buffs.SpecialAttack += item.StatusPoints.SpecialAttack;

	if (Buffs.Health > 0)
	{
		//add our health
		StatusPoints.Health += 5;
		if (StatusPoints.Health > StatusPoints.MaxHealth)
			StatusPoints.Health = StatusPoints.MaxHealth;
		Buffs.Health = 0;
	}

	//now erase it from player's items
	int pos;
	bool found = false;
	for (int i = 0; i < PlayerItems.size(); i++)
	{
		//check if same address
		if (&PlayerItems[i] == itemToConsume)
		{
			//get that position (it has to exist... theoritcally anyway)
			found = true;
			pos = i;
			break;
		}
	}
	//remove item found
	PlayerItems.erase(PlayerItems.begin() + pos);
}
void Player::LevelUp(int skill)
{
	Level += 1;
	switch (skill)
	{
	case 1:
		StatusPoints.MaxHealth += 4;
		break;
	case 2:
		StatusPoints.SpecialAttack += 2;
		break;
	case 3:
		StatusPoints.Attack += 1;
		break;
	case 4:
		StatusPoints.Defence += 1;
		break;
	}
}