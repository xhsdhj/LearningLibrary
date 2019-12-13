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
	//�����ʯ
	lapis.push_back(lapiss);

	//ȥ������
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
	os << "����: " << fixtrue.name
		<< "\t����: " << fixtrue.menPai
		<< "\t״̬: " << (fixtrue.alive ? "[����]" : "[����]")
		<< "\t����: " << fixtrue.level;
	for (size_t i = 0; i < fixtrue.lapis.size(); i++) {
		lapiss = lapiss + fixtrue.lapis[i];
	}
	os << "\t��ʯ:�ۺ� " << lapiss;
	os << "\t����: ";
	if (fixtrue.warcrafts.size() == 0){
		os << "��";
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
		os << "������";
		break;
	case ImmortalLevel::ZHU_JI:
		os << "������";
	case ImmortalLevel::JIE_DAN:
		os << "�ᵤ��";
		break;
	case ImmortalLevel::YUAN_YING:
		os << "ԪӤ��";
		break;
	case ImmortalLevel::HUA_SHEN:
		os << "������";
		break;
	case ImmortalLevel::LIAN_XU:
		os << "������";
		break;
	case ImmortalLevel::HE_TI:
		os << "������";
		break;
	case ImmortalLevel::DA_CHENG:
		os << "�����";
		break;
	case ImmortalLevel::DU_JIE:
		os << "�ɽ���";
		break;
	default:
		break;
	}
	return os;
}
