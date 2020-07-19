#include "stdafx.h"
#include "Character.h"


Character::Character()
{
}


Character::~Character()
{
}

void Character::SetStats(int health, int maxHealth, int attack, int defence, int spattack)
{
	StatusPoints.Health = health;
	StatusPoints.MaxHealth = maxHealth;
	StatusPoints.Attack = attack;
	StatusPoints.Defence = defence;
	StatusPoints.SpecialAttack = spattack;
}