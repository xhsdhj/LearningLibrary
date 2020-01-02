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
	//�����ʯ
	lapis.push_back(lapiss);

	//ȥ������
	warcrafts.erase(warcrafts.begin(), warcrafts.end());
	return true;
}

bool FixTrue::trade(const Warcraft& warcraft)
{
	if (!alive)
	{
		return false;
	}

	//�ж��Ƿ������ָ��������
	if (!hadMonster(warcraft))
	{
		cout << name << " û�� " << warcraft << endl;
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
		cout << other.name << "û��" << warcraft << endl;
		return false;
	}

	//���㵱ǰ��������ʯ�ܼ�
	quickLapis lapi;
	for (size_t i = 0; i < lapis.size(); i++)
	{
		lapi = lapi + lapis[i];
	}

	if (lapi >= warcraft.getValue())
	{
		//����
		quickLapis valueLapi = warcraft.getValue();
		lapi = lapi - valueLapi;
		lapis.clear();					//����Լ�����ʯ
		lapis.push_back(lapi);			//��ӹ��������Ժ����ʯ

		warcrafts.push_back(warcraft);	//��ӹ��������
		other.removeMonster(warcraft);	//�Ƴ����۵�����
		other.lapis.push_back(valueLapi);	//�������ҵ���ʯ
		return true;
	}
	else 
	{
		cout << "��Ǹ!" << name << "����ʯ������" << warcraft << endl;
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
		cout << name << "û��" << warcraft << endl;
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

	//�Է������߸�Ǯ
	otherLapi = otherLapi - warcraft.getValue();
	other.lapis.clear();
	other.lapis.push_back(otherLapi);
	//�Է�������������01
	other.warcrafts.push_back(warcraft);
	
	//�����Ƴ�����,��Ǯ
	this->removeMonster(warcraft);
	this->lapis.push_back(warcraft.getValue());

	return true;
}

int FixTrue::getPower() const
{
	//���������߼����ս����
	int ret = ((int)level + 1) * FIXTRUE_LEVEL_FACTOR;

	//������ʯ������ս����
	quickLapis lapi;
	for (size_t i = 0; i < lapis.size(); i++)
	{
		lapi = lapi + lapis[i];
	}
	ret += (lapi.getCount() * QUICKLAPIS_FACTOR);

	//�����������޵�����ս����
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
	//����һ��������(��һ�������ָ��, ָ�� warcrafts �е�һ����Ա)
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
