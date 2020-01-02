#pragma once
#include <string>
#include <iostream>

using namespace std;

class quickLapis;

/*������*/
class Warcraft
{
public:
	Warcraft(int level = 1, const string& category = "δ֪");
	~Warcraft();

	quickLapis getValue() const;

	int getPower() const;//��ȡ�����޵�ս����

	friend ostream& operator<<(ostream& os, 
		const Warcraft& monster);

	friend bool operator==(const Warcraft& one,
		const Warcraft& other);
private:
	string category;//���޵�����
	int level;		//1-9��

};

ostream& operator<<(ostream& os, 
	const Warcraft& monster);
bool operator==(const Warcraft& one,
	const Warcraft& other);