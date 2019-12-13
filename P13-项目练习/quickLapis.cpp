#include "quickLapis.h"
#include <sstream>

quickLapis::quickLapis(int count, QuickLapisLeve1 level)
{
	this->count = count;
	this->level = level;
}

quickLapis::~quickLapis()
{
}

string quickLapis::str() const
{
	stringstream ret;
	ret << count << " 块 ";

	switch (level) {
	case QuickLapisLeve1::PRIMARY_LEVEL:
		ret << "初级灵石";
		break;
	case QuickLapisLeve1::MIDDLE_LEVEL:
		ret << "中级灵石";
		break;
	case QuickLapisLeve1::ADVANCE_LEVEL:
		ret << "高级灵石";
		break;
	default:
		ret << "未知灵石";
		break;
	}
	return ret.str();
}


ostream& operator<<(ostream& os, const quickLapis& stone)
{
	os << stone.str();
	return os;
}

quickLapis quickLapis::operator+(const quickLapis& stone)
{
	int sum = 0;
	if (stone.level == QuickLapisLeve1::PRIMARY_LEVEL) {
		sum += stone.count;
	}
	else if (stone.level == QuickLapisLeve1::MIDDLE_LEVEL) {
		sum += stone.count * 10;
	}
	else if (stone.level == QuickLapisLeve1::ADVANCE_LEVEL) {
		sum += stone.count * 100;
	}

	if (this->level == QuickLapisLeve1::PRIMARY_LEVEL) {
		sum += this->count;
	}
	else if (this->level == QuickLapisLeve1::MIDDLE_LEVEL) {
		sum += this->count * 10;
	}
	else if (this->level == QuickLapisLeve1::ADVANCE_LEVEL) {
		sum += this->count * 100;
	}

	return quickLapis(sum, QuickLapisLeve1::PRIMARY_LEVEL);
}
