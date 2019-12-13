#include "Warcraft.h"
#include "quickLapis.h"

Warcraft::Warcraft(int level, const string& category)
{
	this->level = level;
	this->category = category;
}

Warcraft::~Warcraft()
{
}

quickLapis Warcraft::getValue()
{
	/*妖兽各等级的价值*/
	int stoneCount[] = { 100,200,500,1000,2000,5000,10000,20000,100000 };
	int count = stoneCount[level - 1];
	return quickLapis(count, QuickLapisLeve1::PRIMARY_LEVEL);
}

ostream& operator<<(ostream& os, const Warcraft& monster) {
	os << monster.level << " 级 " 
		<< monster.category << " 妖兽 ";
	return os;
}
