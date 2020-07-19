// Hero's Quest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include "Monster.h"
#include "Player.h"
#include "Item.h"
#include <vector>

using namespace std;

//index of monster I am fighting
int MonsterIndex = 0; //0 by default. 0 based index
const int NumberOfMonsters = 5;
//My 4 monsters
Monster Monsters[NumberOfMonsters];
//Item Array
const int Itemcount = 7;
Item Items[Itemcount];
//Player
Player MyPlayer;
//win or lose
bool WinGame;
string winMap[10] =
{
	"     .`        .` `:.                                            ",
	".MN.      yM+ /ms            .s/                                 ",
	" +Mh     :Mh  `:.    `://-  -oMh::.   `://:`    .:`./:`-:`    `:.",
	"  hM+   `NN.  /Ms  `yMyoohm oyMmss: .hNyooyMd.  oMdmsy:oMy    hM/",
	"  `NM.  yM/   /Ms  yM+       :My    mM-    /Md  oMy     hM/  +Ms ",
	"   :Md /My    /Ms  mM.       :My   `MM     .MN  oM+     `NN..Nm  ",
	"    sMyNm`    /Ms  sMy   `/  :Mh    hMo   `yMo  oM+      -MddN.  ",
	"    `dMN-     /Mo   odNmmms   yNmm+ `odNddmh/   oM/       +MM/   ",
	"                       `                `                 +My    ",
	"                                                         .md`    "
};
string deathMap[7] =
{
	"  `/osss+`   -s`    /o       oo:    ++    -+sss+-    `mo",
	" /Ny:``-yM+  +M.    hN       NmM+   dd  `dm/.`.+Nh`  `Ms",
	"`Nh      hM` +M:....hN       Ny:Mo  dd  yM.     /M+  `Mo",
	"-Mo      sM. +MyssssmN       Ny :Ns dd  dN      -Mo  `Mo",
	" Nd     `mm  +M.    hN       Ny  -Nydd  sM-     sM-   y:",
	" -dmo++smh.  +M.    hN       Ny   .mMd  `sNy++odm:   .do",
	"   `:::-`    `:     .-       -.    `-.     -:::.      -."
};


//delay voids for unix or windows
#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)

#include <windows.h>

inline void delay(unsigned long ms)
{
	Sleep(ms);
	//for debug
	//Sleep(0);
}

#else  /* presume POSIX */

#include <unistd.h>

inline void delay(unsigned long ms)
{
	usleep(ms * 1000);
}

#endif 
//prints a centred string on the console
void CentreString(char* input)
{
	int l = strlen(input);
	int pos = (int)((80 - l) / 2);
	for (int i = 0; i<pos; i++)
		cout << " ";

	cout << input << endl;
}
//returns a 10 string long health bar
string GetHealthBar(float current, float max)
{
	stringstream outputS;
	outputS << (int)current << " [";
	float perdec = current * 10. / max;
	for (int i = 0; i < (int)perdec; i++)
		outputS << ":";
	for (int i = 0; i < 10- perdec; i++)
		outputS << " ";
	outputS << "]";
	return outputS.str();
}
//Print current screen of the game
//Player and map
void PrintGameScreen()
{
	//Print Status
	stringstream printLS;
	//gap of 2
	printLS << "  ";
	printLS << Monsters[MonsterIndex].Name << "    Health: ";
	if (Monsters[MonsterIndex].StatusPoints.Health < 0)
		printLS << GetHealthBar(0,
			Monsters[MonsterIndex].StatusPoints.MaxHealth);
	else
		printLS << GetHealthBar(Monsters[MonsterIndex].StatusPoints.Health,
			Monsters[MonsterIndex].StatusPoints.MaxHealth);
	string LH = printLS.str();

	stringstream printRS;
	printRS << MyPlayer.Name << "    Health: " <<
		GetHealthBar(MyPlayer.StatusPoints.Health,
			MyPlayer.StatusPoints.MaxHealth) <<
		" $" << MyPlayer.GetPrizeMoney();
	string RH = printRS.str();

	//print monster stats
	cout << LH;
	//screen is 80 long, take 2 from the side (RH)
	for (int i = 0; i < 78 - RH.length() - LH.length(); i++)
		cout << " ";
	//Print player stats
	cout << RH << endl;

	for (int i = 0; i < 3; i++)
		cout << endl;

	//Print GameScreen

}
bool GoShopping()
{
	//show buy menu
	system("cls");
	PrintGameScreen();
	cout << "  Item";
	for (int i = 0; i < 16; i++)
		cout << " ";
	cout << "Description";
	for (int i = 0; i < 9; i++)
		cout << " ";
	cout << "Cost";
	//endline and add spacer
	cout << endl << endl;
	bool hasItem[Itemcount]; //initall false
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < Itemcount; i++)
	{
		hasItem[i] = false;
		//see if Player has item
		for (int k = 0; k < MyPlayer.PlayerItems.size(); k++)
		{
			//checking by name
			if (MyPlayer.PlayerItems[k].Name == Items[i].Name)
			{
				hasItem[i] = true;
				//change colour-red
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			}
		}
		cout << "  " << Items[i].Name;
		int Gap = 16 - Items[i].Name.length();
		for (int k = 0; k < Gap; k++)
			cout << " ";
		cout << Items[i].Description;
		Gap = 25 - Items[i].Description.length();
		for (int k = 0; k < Gap; k++)
			cout << " ";
		cout << "$" << Items[i].GetCost();
		Gap = 4;
		for (int k = 0; k < Gap; k++)
			cout << " ";
		cout << "#" << i + 1;
		if (hasItem[i] == false)
			cout << endl;
		else
			cout << "     You have one" << endl;
		//return normal colour to console
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
	cout << endl;
	cout << "What item would you like to purchse? (integer) or would you like to cancel (c)" << endl;
	while (true)
	{
		string read;
		cin >> read;
		if (read != "c")
		{
			try
			{
				//select item to purchase
				int number = atoi(read.c_str());
				if (number > 0)
				{
					if (number < Itemcount + 1)
					{
						if (Items[number - 1].GetCost() <= MyPlayer.GetPrizeMoney())
						{
							if (hasItem[number - 1] == false)
							{
								//purchase
								MyPlayer.AddItem(Items[number - 1]);
								return false;
								break;
							}
							else
							{
								cout << "You already have this item, you cannot have multiple. Please input again" << endl;
							}
						}
						else
						{
							cout << "Cannot buy, insufficient money. Please input again" << endl;
						}
					}
					else cout << "Integer not in range" << endl;
				}
				else cout << "Integer not in range" << endl;
			}
			catch (exception e)
			{
				cout << "Integer must be in range seen in the above table. Please input again" << endl;
			}
		}
		else
		{
			return true;
			break;
		}
	}
}
void PlayerWinsFight()
{
	//Prize Money-2 from fight + monster value
	MyPlayer.AddPrizeMoney(Monsters[MonsterIndex].Value + 1);

	system("cls");
	PrintGameScreen();

	//Print out the victory
	for (int i = 0; i < (sizeof(winMap) / sizeof(*winMap)); i++)
	{
		string lineToCentre;
		lineToCentre.append(winMap[i]);
		CentreString(&lineToCentre[0u]);
	}
	cout << "Congratulations, you have won the fight!" << endl;

	//delay the victory sign
	delay(1000);

	//move index on
	MonsterIndex += 1;
	//any leveling up for 3rd, 4th and final monsters
	if (MonsterIndex == 2 | MonsterIndex == 3 | MonsterIndex == 4)
	{
		int skill; //by default
		cout << endl;
		cout << "Congratulations, you can now level up!" << endl;
		cout << "Select a stat to improve:" << endl;
		cout << "(1) Health: + 4 hitpoints (max hitpoints)" << endl;
		cout << "(2) Attack: + 1 attack point" << endl;
		cout << "(3) Special Attack: + 2 special attack points" << endl;
		cout << "(4) Defence: + 1 defence point" << endl;
		while (true)
		{
			string read;
			cin >> read;
			try
			{
				int number = atoi(read.c_str());
				//check if in range and break loop if it is
				if (number < 5)
				{
					if (number > 0)
					{
						skill = number;
						break;
					}
					else
					{
						cout << "Integer too small, please try again" << endl;
					}
				}
				else
				{
					cout << "Integer too large, please try again" << endl;
				}
			}
			catch (exception e)
			{
				cout << "Invalid integer, please try again";
			}
		}

		MyPlayer.LevelUp(skill);
	}

	if (MonsterIndex < 5)
	{
		cout << "Do you wish to buy an item (y/n)?" << endl;
		bool response;
		while (true)
		{
			string read;
			cin >> read;
			if (read == "y")
			{
				response = true;
				break;
			}
			else
			{
				if (read == "n")
				{
					response = false;
					break;
				}
				else cout << "Invalid input, please try again" << endl;
			}
		}

		bool DidCancel = true;
		if (response == true)
			DidCancel = GoShopping();

		//loop again
		bool loopagain = false;
		if (DidCancel == false & response == true)
			loopagain = true;
		while (loopagain)
		{
			cout << "Do you wish to buy another item (y/n)?" << endl;
			while (true)
			{
				string read;
				cin >> read;
				if (read == "y")
				{
					response = true;
					break;
				}
				else
				{
					if (read == "n")
					{
						response = false;
						break;
					}
					else cout << "Invalid input, please try again" << endl;
				}
			}
			if (response == true)
				DidCancel = GoShopping();
			else
				break;
		}

		//health
		MyPlayer.ResetRound();
	}
}
void Initialise()
{
	//initialise Monsters
	for (int i = 0; i < NumberOfMonsters; i++)
	{
		stringstream name;
		name << "Monster " << (i + 1);
		Monsters[i] = Monster(name.str(), i + 1);
	}
	Monsters[NumberOfMonsters] = Monster("The UFC", NumberOfMonsters);

	//Items array
	for (int i = 0; i < Itemcount; i++)
		Items[i].SetType(i+1);

	//Player get name
	string playerName;
	cout << "What is the player name?" << endl;
	cin >> playerName;
	MyPlayer = Player(playerName);
}
void PrintDeathScreen()
{
	//change colour-red
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	//draw death strings-centered
	for (int i = 0; i < (sizeof(deathMap) / sizeof(*deathMap)); i++)
	{
		string lineToCentre;
		lineToCentre.append(deathMap[i]);
		CentreString(&lineToCentre[0u]);
	}
	CentreString("You have died :'(");
	//return normal colour to console
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void ConsumeItem()
{
	int size = MyPlayer.PlayerItems.size();
	if (size > 0)
	{
		//check if player has any consumables (bool check)
		//add referenc to it to vector
		vector<Item*> consumableItems;
		bool anyConsumables = false;
		for (int i = 0; i < size; i++)
		{
			if (MyPlayer.PlayerItems[i].IsConsumable() == true)
			{
				anyConsumables = true;
				consumableItems.push_back(&MyPlayer.PlayerItems[i]);
			}
		}
		if (anyConsumables == true)
		{
			cout << "  Item";
			for (int i = 0; i < 16; i++)
				cout << " ";
			cout << "Description";
			//endline and add spacer
			cout << endl << endl;
			for (int i = 0; i < consumableItems.size(); i++)
			{
				Item item = *consumableItems[i];
				cout << "  " << item.Name;
				int Gap = 16 - item.Name.length();
				for (int k = 0; k < Gap; k++)
					cout << " ";
				cout << item.Description;
				Gap = 24 - item.Description.length();
				for (int k = 0; k < Gap; k++)
					cout << " ";
				cout << "#" << i + 1 << endl;
			}

			cout << "Which consumable item do you wish to use? (integer) or cancel (c)" << endl;

			while (true)
			{
				string read;
				cin >> read;
				if (read != "c")
				{
					try
					{
						//select item to consume
						int number = atoi(read.c_str());
						MyPlayer.ConsumeItem(consumableItems[number - 1]);
						cout << "Item consumed!" << endl;
						break;
					}
					catch (exception e)
					{
						cout << "Integer must be in range seen in the above table" << endl;
					}
				}
				else break;
			}
		}
		else cout << "Player has no consumable items" << endl;
	}
	else cout << "Player has no items" << endl;

	delay(400);
}
void PrintVictoryScreen()
{
	//change colour-red
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	//draw death strings-centered
	for (int i = 0; i < (sizeof(winMap) / sizeof(*winMap)); i++)
	{
		string lineToCentre;
		lineToCentre.append(winMap[i]);
		CentreString(&lineToCentre[0u]);
	}
	CentreString("You are the champion!");
	//return normal colour to console
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	CentreString("el fino!");
}
int main()
{
	//seed random number
	srand(time(NULL));

	//intialise arrays and classes
	Initialise();

	//set white colour
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	//keep game in play
	while (true)
	{
		system("cls");
		PrintGameScreen();

		bool bspecialattk = false;

		//get user input
		while (true)
		{
			cout << "What would you like to do?" << endl;
			cout << "Use item (i)";
			if (MyPlayer.GetUsedSpcAttck() == false)
				cout << ", Special attack (s)";
			cout << " or make a regular attack (a)?" << endl;
			string read;
			cin >> read;
			if (read == "i")
			{
				ConsumeItem();
				system("cls");
				PrintGameScreen();
			}
			else if (read == "a")
				break;
			else if (MyPlayer.GetUsedSpcAttck() == false)
				if (read == "s")
				{
					bspecialattk = true;
					break;
				}
				else cout << "invalid input, please try again" << endl;
			else
				cout << "invalid input, please try again" << endl;
		}

		system("cls");
		PrintGameScreen();
		//automated from here on

		//Battle it out
		//break condition-if monster is alive or not
		bool LetMonsterAttack = true;

		//Hero makes attack
		int damageDealt = MyPlayer.AttackMonster(
			&Monsters[MonsterIndex], bspecialattk);
		if (damageDealt == 0)
			CentreString("Your attack was blocked!");
		else
		{
			stringstream printStr;
			printStr << "Damage dealt: " << damageDealt;
			CentreString(&printStr.str()[0u]);
		}

		//check if monster died
		if (Monsters[MonsterIndex].StatusPoints.Health < 1)
		{
			//PlayerWon
			LetMonsterAttack = false;
			PlayerWinsFight();
			if (MonsterIndex == 5)
			{
				WinGame = true;
				break;
			}
		}

		//dealy it for 1 second
		delay(1000);

		if (LetMonsterAttack == true)
		{
			//Monster makes attack
			//First check for special attack
			if (MonsterIndex == 4)
			{
				// 1/6 chance of being special attack
				int random = rand() % 6;
				if (random == 0)
					if (Monsters[MonsterIndex].GetUsedSpcAttck() == false)
						bspecialattk = true;
					else bspecialattk = false;
				else
					bspecialattk = false;
			}
			damageDealt = Monsters[MonsterIndex].AttackPlayer(
				&MyPlayer, bspecialattk);
			if (damageDealt == 0)
				CentreString("You blocked the attack!");
			else
			{
				stringstream printStr;
				printStr << "Damage dealt to you: " << damageDealt;
				CentreString(&printStr.str()[0u]);
			}
			//dealy it for 1 second
			delay(1000);

			//check if player died
			if (MyPlayer.StatusPoints.Health < 1)
			{
				break;
				WinGame = false;
			}
		}
	}

	if (WinGame == false)
		PrintDeathScreen();
	else 
		PrintVictoryScreen();

	system("pause");
    return 0;
}