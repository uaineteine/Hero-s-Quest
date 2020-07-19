#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Character.h"
#include "Item.h"

class Monster;

using namespace std;

	class Player : public Character
	{
	public:
		//default
		Player();
		Player(string name);
		~Player();

		//Both the buffs and player items are edited at the top level
		Stats Buffs;
		vector<Item> PlayerItems;

		int AttackMonster(Monster* monsterToAttack, bool special);
		void ConsumeItem(Item* itemToConsume);
		void ResetRound();
		void AddItem(Item itemToAdd);
		void LevelUp(int skill);
		void AddPrizeMoney(int prize)
		{
			PrizeMoney += prize;
		}
		int GetPrizeMoney()
		{
			return PrizeMoney;
		}
		bool GetUsedSpcAttck()
		{
			return UsedSpcAttck;
		}

	private:
		//these are not wanted to be edited outside of the class
		bool UsedSpcAttck;
		int PrizeMoney;
		int Level;
	};
#endif
