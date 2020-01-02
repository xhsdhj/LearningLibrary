#include "FixTrue.h"
#include "quickLapis.h"
#include "Warcraft.h"

#define FIXTRUE_LEVEL_FACTOR	1000
#define QUICKLAPIS_FACTOR		0.1
#define WARCRAFT_FACTOR			0.1

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
	if (!alive)
	{
		return false;
	}

	//判断是否有这个指定的妖兽
	if (!hadMonster(warcraft))
	{
		cout << name << " 没有 " << warcraft << endl;
		return false;
	}

	quickLapis lapi = warcraft.getValue();
	lapis.push_back(lapi);
	removeMonster(warcraft);

	return true;
}

bool FixTrue::trade(FixTrue& other, const Warcraft& warcraft)
{
	if (alive == false || other.alive == false)
	{
		return false;
	}

	if (!other.hadMonster(warcraft))
	{
		cout << other.name << "没有" << warcraft << endl;
		return false;
	}

	//计算当前的所有灵石总价
	quickLapis lapi;
	for (size_t i = 0; i < lapis.size(); i++)
	{
		lapi = lapi + lapis[i];
	}

	if (lapi >= warcraft.getValue())
	{
		//购买
		quickLapis valueLapi = warcraft.getValue();
		lapi = lapi - valueLapi;
		lapis.clear();					//清空自己的灵石
		lapis.push_back(lapi);			//添加购买妖兽以后的灵石

		warcrafts.push_back(warcraft);	//添加购买的妖兽
		other.removeMonster(warcraft);	//移除出售的妖兽
		other.lapis.push_back(valueLapi);	//增加卖家的灵石
		return true;
	}
	else 
	{
		cout << "抱歉!" << name << "的灵石不够买" << warcraft << endl;
		return false;
	}
}

bool FixTrue::trade(const Warcraft& warcraftSource, FixTrue& other, const Warcraft& warcraftDest)
{
	if (alive == false || other.alive == false)
	{
		return false;
	}

	if (warcraftSource == warcraftDest ||
		!hadMonster(warcraftSource)||
		!other.hadMonster(warcraftDest)||
		!(warcraftSource.getValue() >= warcraftDest.getValue()))
	{
		return false;
	}

	removeMonster(warcraftSource);
	other.removeMonster(warcraftDest);
	warcrafts.push_back(warcraftDest);
	other.warcrafts.push_back(warcraftSource);

	return true;
}

bool FixTrue::trade(const Warcraft& warcraft, FixTrue& other)
{
	if (this->alive == false || other.alive == false)
	{
		return false;
	}

	if (!hadMonster(warcraft))
	{
		cout << name << "没有" << warcraft << endl;
		return false;
	}

	quickLapis otherLapi;
	for (size_t i = 0; i < other.lapis.size(); i++)
	{
		otherLapi = otherLapi + other.lapis[i];
	}

	if (!(otherLapi >= warcraft.getValue()))
	{
		return false;
	}

	//对方修真者付钱
	otherLapi = otherLapi - warcraft.getValue();
	other.lapis.clear();
	other.lapis.push_back(otherLapi);
	//对方修真者收妖兽01
	other.warcrafts.push_back(warcraft);
	
	//己方移除妖兽,收钱
	this->removeMonster(warcraft);
	this->lapis.push_back(warcraft.getValue());

	return true;
}

int FixTrue::getPower() const
{
	//计算修真者级别的战斗力
	int ret = ((int)level + 1) * FIXTRUE_LEVEL_FACTOR;

	//计算灵石助攻的战斗力
	quickLapis lapi;
	for (size_t i = 0; i < lapis.size(); i++)
	{
		lapi = lapi + lapis[i];
	}
	ret += (lapi.getCount() * QUICKLAPIS_FACTOR);

	//计算所有妖兽的助攻战斗力
	for (size_t i = 0; i < warcrafts.size(); i++)
	{
		ret += warcrafts[i].getPower()* WARCRAFT_FACTOR;
	}

	return ret;
}

void FixTrue::fight(const Warcraft& warcraft)
{
	int selfPower = getPower();
	int warcraftPower = warcraft.getPower();

	if (selfPower > warcraftPower)
	{
		warcrafts.push_back(warcraft);
	}
	else if (selfPower < warcraftPower)
	{
		dead();
	}
}

void FixTrue::dead()
{
	alive = false;
	lapis.erase(lapis.begin(),lapis.end());
	warcrafts.erase(warcrafts.begin(), warcrafts.end());
}

bool FixTrue::hadMonster(const Warcraft& warcraft)
{
	for (size_t i = 0; i < warcrafts.size(); i++)
	{
		if (warcraft == warcrafts[i])
		{
			return true;
		}
	}

	return false;
}

bool FixTrue::removeMonster(const Warcraft& warcraft)
{
	//定义一个迭代器(是一种特殊的指针, 指向 warcrafts 中第一个成员)
	vector<Warcraft>::iterator it = warcrafts.begin();
	while( it != warcrafts.end())
	{
		if (*it == warcraft)
		{
			it = warcrafts.erase(it);
			return true;
		}
		else 
		{
			it++;
		}
	}
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
