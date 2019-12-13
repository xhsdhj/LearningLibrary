#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class quickLapis;
class Warcraft;

enum class ImmortalLevel {
	LIAN_QI,		//������
	ZHU_JI,			//������
	JIE_DAN,		//�ᵤ��
	YUAN_YING,		//ԪӤ��
	HUA_SHEN,		//������
	LIAN_XU,		//������
	HE_TI,			//������
	DA_CHENG,		//�����
	DU_JIE			//�ɽ���
};

//��������
class FixTrue
{
public:
	FixTrue(const char* name, const char* menPai, ImmortalLevel level);
	~FixTrue();

	//�ڿ�
	void mining();

	//���г��������е�����
	bool trade();

	//���г���ָ��������
	bool trade(const Warcraft& warcraft);

	//���Լ�����ʯ,���������������ߵ�ָ������
	bool trade(FixTrue& other, const Warcraft& warcraft);

	//���Լ�ָ��������,�������������ߵ�ָ������
	bool trade(const Warcraft& warcraftSource, FixTrue& other, const Warcraft& warcraftDest);

	//���Լ�������,����������������,�Ի�ȡ��ʯ
	bool trade(const Warcraft& warcraft, FixTrue& other);

	//��ȡս����
	int getPower() const;

	//��������
	bool fight(const Warcraft& warcraft);

	friend ostream& operator<<(ostream& os, const FixTrue& fixtrue);
	friend ostream& operator<<(ostream& os, const ImmortalLevel level);

private:
	string name;				//����
	string menPai;				//����
	ImmortalLevel level;		//�����ߵļ���
	vector<quickLapis> lapis;	//��ʯ�ʲ�
	vector<Warcraft> warcrafts;	//�����ʲ�
	bool alive;					//����״̬
};

ostream& operator<<(ostream& os, const FixTrue& fixtrue);
ostream& operator<<(ostream& os, const ImmortalLevel level);