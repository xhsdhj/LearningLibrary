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

	quickLapis getValue();
	friend ostream& operator<<(ostream& os, 
		const Warcraft& monster);
private:
	string category;//���޵�����
	int level;		//1-9��

};

ostream& operator<<(ostream& os, 
	const Warcraft& monster);