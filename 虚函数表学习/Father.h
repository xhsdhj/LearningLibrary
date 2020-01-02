#pragma once
#include <iostream>

using namespace std;

typedef void(*func_t)(void);

class Father
{
public:
	virtual void func1();
	virtual void func2();
	virtual void func3();
	void func4();

public:
	int x = 200;
	int y = 300;
	static int z;
};

