#include "FixTrue.h"
#include "quickLapis.h"
#include "Warcraft.h"

FixTrue::FixTrue(const char* name, const char* menPai, ImmortalLevel level)
{
	this->name = name;
	this->menPai = menPai;
	this->level = level;
	this->alive = true;
}

FixTrue::~FixTrue()
{
}

void FixTrue::mining()
{
	lapis.push_back(quickLapis(100, QuickLapisLeve1::PRIMARY_LEVEL));
}

bool FixTrue::trade()
{
	if (!alive) {
		return false;
	}
	quickLapis lapiss;
	for (size_t i = 0; i < warcrafts.size(); i++) {
		lapiss = lapiss + warcrafts[i].getValue();
	}
	//添加灵石
	lapis.push_back(lapiss);

	//去掉妖兽
	warcrafts.erase(warcrafts.begin(), warcrafts.end());
	return true;
}

bool FixTrue::trade(const Warcraft& warcraft)
{
	return false;
}

bool FixTrue::trade(FixTrue& other, const Warcraft& warcraft)
{
	return false;
}

bool FixTrue::trade(const Warcraft& warcraftSource, FixTrue& other, const Warcraft& warcraftDest)
{
	return false;
}

bool FixTrue::trade(const Warcraft& warcraft, FixTrue& other)
{
	return false;
}

int FixTrue::getPower() const
{
	return 0;
}

bool FixTrue::fight(const Warcraft& warcraft)
{
	return false;
}

ostream& operator<<(ostream& os, const FixTrue& fixtrue)
{
	quickLapis lapiss;
	os << "姓名: " << fixtrue.name
		<< "\t门派: " << fixtrue.menPai
		<< "\t状态: " << (fixtrue.alive ? "[在修]" : "[死亡]")
		<< "\t级别: " << fixtrue.level;
	for (size_t i = 0; i < fixtrue.lapis.size(); i++) {
		lapiss = lapiss + fixtrue.lapis[i];
	}
	os << "\t灵石:折合 " << lapiss;
	os << "\t妖兽: ";
	if (fixtrue.warcrafts.size() == 0){
		os << "无";
	}
	else {
		for (size_t i = 0; i < fixtrue.warcrafts.size(); i++){
			os << fixtrue.warcrafts[i] << " ";
		}
	}
	return os;
}

ostream& operator<<(ostream& os, const ImmortalLevel level)
{
	switch (level)
	{
	case ImmortalLevel::LIAN_QI:
		os << "炼气期";
		break;
	case ImmortalLevel::ZHU_JI:
		os << "筑基期";
	case ImmortalLevel::JIE_DAN:
		os << "结丹期";
		break;
	case ImmortalLevel::YUAN_YING:
		os << "元婴期";
		break;
	case ImmortalLevel::HUA_SHEN:
		os << "化神期";
		break;
	case ImmortalLevel::LIAN_XU:
		os << "炼虚期";
		break;
	case ImmortalLevel::HE_TI:
		os << "合体期";
		break;
	case ImmortalLevel::DA_CHENG:
		os << "大乘期";
		break;
	case ImmortalLevel::DU_JIE:
		os << "渡劫期";
		break;
	default:
		break;
	}
	return os;
}
