#include "stdafx.h"
#include "BossMonster.h"
#include <time.h>

BossMonster::BossMonster(string name)
{
	Name = name;
	SetStats(50, 50, 8, 8, 5);
}


BossMonster::~BossMonster()
{
}
