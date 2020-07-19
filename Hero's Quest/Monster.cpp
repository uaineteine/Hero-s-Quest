#include "stdafx.h"
#include "Monster.h"
#include "Player.h";

Monster::Monster()
{
}
Monster::Monster(string name, int type)
{
	Name = name;
	UsedSpcAttck = false;
	/*
	//seed random number
	srand(time(NULL));
	int health = (rand() % 50) + 50;
	int maxHealth = 100;
	//declaring here that attack cannot be 0
	int attack = (rand() % 9) + 1;
	int defence = rand() % 10;
	//set all stats above without special attack
	SetStats(health, maxHealth, attack, defence, 0);*/
	if (type == 1)
		SetStats(10, 10, 1, 1, 0);
	else if (type == 2)
		SetStats(20, 20, 3, 2, 0);
	else if (type == 3)
		SetStats(30, 30, 5, 4, 0);
	else if (type == 4)
		SetStats(40, 40, 6, 7, 0);
	else
		SetStats(50, 50, 8, 8, 5);
	//Value is sum of attck and def
	Value = StatusPoints.Attack + 
		StatusPoints.Defence;
}


Monster::~Monster()
{
}

int Monster::AttackPlayer(Player* playertoAttack, bool special)
{
	Player ThePlayer = *playertoAttack;
	//1-6 bonus attack
	int attckBonus = (rand() % 6) + 1;
	if (special == true)
		attckBonus += StatusPoints.SpecialAttack;

	if (UsedSpcAttck == false)
		UsedSpcAttck = special;

	//1-6 bonus defence for the player
	int defenceBonus = (rand() % 6) + 1;

	int difference = StatusPoints.Attack + attckBonus -
		(defenceBonus + ThePlayer.StatusPoints.Defence + ThePlayer.Buffs.Defence);
	if (difference > 0)
	{
		//take damage from monster
		ThePlayer.StatusPoints.Health -= difference;
		//set variable back
		*playertoAttack = ThePlayer;
		return difference;
	}
	//no damage dealt-blocked
	else return 0;
}