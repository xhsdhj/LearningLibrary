#pragma once
#include <string>
#include <iostream>

using namespace std;

class quickLapis;

/*妖兽类*/
class Warcraft
{
public:
	Warcraft(int level = 1, const string& category = "未知");
	~Warcraft();

	quickLapis getValue() const;

	int getPower() const;//获取该妖兽的战斗力

	friend ostream& operator<<(ostream& os, 
		const Warcraft& monster);

	friend bool operator==(const Warcraft& one,
		const Warcraft& other);
private:
	string category;//妖兽的种类
	int level;		//1-9级

};

ostream& operator<<(ostream& os, 
	const Warcraft& monster);
bool operator==(const Warcraft& one,
	const Warcraft& other);