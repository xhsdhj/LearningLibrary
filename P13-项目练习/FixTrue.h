#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class quickLapis;
class Warcraft;

enum class ImmortalLevel {
	LIAN_QI,		//炼气期
	ZHU_JI,			//筑基期
	JIE_DAN,		//结丹期
	YUAN_YING,		//元婴期
	HUA_SHEN,		//化神期
	LIAN_XU,		//炼虚期
	HE_TI,			//合体期
	DA_CHENG,		//大乘期
	DU_JIE			//渡劫期
};

//修真者类
class FixTrue
{
public:
	FixTrue(const char* name, const char* menPai, ImmortalLevel level);
	~FixTrue();

	//挖矿
	void mining();

	//到市场售卖所有的妖兽
	bool trade();

	//到市场卖指定的妖兽
	bool trade(const Warcraft& warcraft);

	//用自己的灵石,来购买其他修真者的指定妖兽
	bool trade(FixTrue& other, const Warcraft& warcraft);

	//用自己指定的妖兽,来和其他修真者的指定妖兽
	bool trade(const Warcraft& warcraftSource, FixTrue& other, const Warcraft& warcraftDest);

	//把自己的妖兽,售卖给其他修真者,以换取灵石
	bool trade(const Warcraft& warcraft, FixTrue& other);

	//获取战斗力
	int getPower() const;

	//捕获妖兽
	bool fight(const Warcraft& warcraft);

	friend ostream& operator<<(ostream& os, const FixTrue& fixtrue);
	friend ostream& operator<<(ostream& os, const ImmortalLevel level);

private:
	string name;				//姓名
	string menPai;				//门派
	ImmortalLevel level;		//修行者的级别
	vector<quickLapis> lapis;	//灵石资产
	vector<Warcraft> warcrafts;	//妖兽资产
	bool alive;					//生死状态
};

ostream& operator<<(ostream& os, const FixTrue& fixtrue);
ostream& operator<<(ostream& os, const ImmortalLevel level);