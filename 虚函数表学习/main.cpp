#include <iostream>
#include <fstream>

#include "Father.h"
using namespace std;

int main() {
	Father father;
	cout << "sizeof(father) == " << sizeof(father) << endl;

	cout << "对象地址: " << (int*)&father << endl;
	int* vptr = (int*)*(int*)(&father);

	cout << "调用第一个虚函数: \n";
	((func_t)*(vptr+0))();
	cout << "调用第二个虚函数: \n";
	((func_t)*(vptr+1))();
	cout << "调用第三个虚函数: \n";
	((func_t)*(vptr+2))();

	cout << "第一个数据成员的地址: " << endl;
	cout << &father.x << endl;
	cout << hex << (int)&father + 4 << endl;
	cout << "第一个数据成员的值: " << endl;
	cout << dec << father.x << endl;
	cout << *(int*)((int)&father + 4) << endl;

	cout << "第二个数据成员的地址: " << endl;
	cout << &father.y << endl;
	cout << hex << (int)&father + 8 << endl;
	cout << "第二个数据成员的值: " << endl;
	cout << dec << father.y << endl;
	cout << *(int*)((int)&father + 8) << endl;
	return 0;
}