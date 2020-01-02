#pragma once
#include <string>
#include <iostream>

using namespace std;

typedef enum class _QuickLapisLevel {
	PRIMARY_LEVEL,
	MIDDLE_LEVEL,
	ADVANCE_LEVEL,
	SPRITE_STONE_LEVEL_COUNT
}QuickLapisLeve1;

//灵石类
class quickLapis
{
public:

	quickLapis(int conut = 0,
		QuickLapisLeve1 level = QuickLapisLeve1::PRIMARY_LEVEL);
	~quickLapis();

	string str() const;
	friend ostream& operator<<(ostream& os,
		const quickLapis& stone);
	quickLapis operator+(const quickLapis& lapi);
	quickLapis operator-(const quickLapis& lapi);
	int getCount() const;

	bool operator>=(const quickLapis& lapi);
private:
	int count;				//灵石的数量: xxx块
	QuickLapisLeve1 level;	//灵石的等级
};

ostream& operator<<(ostream& os, 
	const quickLapis& stone);
//quickLapis operator+(const quickLapis& stone);