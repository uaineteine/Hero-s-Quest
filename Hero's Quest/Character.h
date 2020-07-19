#pragma once

#include <string>

using namespace std;

class Character
{
protected:
	struct Stats
	{
		int MaxHealth = 0;
		int Health = 0;
		int Attack = 0;
		int Defence = 0;
		int SpecialAttack = 0;
	};
	void SetStats(int health, int maxHealth,  int attack, int defence, int spattack);
public:
	Character();
	~Character();
	struct Stats StatusPoints;
	string Name;
};
