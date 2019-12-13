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

	quickLapis getValue();
	friend ostream& operator<<(ostream& os, 
		const Warcraft& monster);
private:
	string category;//妖兽的种类
	int level;		//1-9级

};

ostream& operator<<(ostream& os, 
	const Warcraft& monster);