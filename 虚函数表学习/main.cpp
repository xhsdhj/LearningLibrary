#include <iostream>
#include <fstream>

#include "Father.h"
using namespace std;

int main() {
	Father father;
	cout << "sizeof(father) == " << sizeof(father) << endl;

	cout << "�����ַ: " << (int*)&father << endl;
	int* vptr = (int*)*(int*)(&father);

	cout << "���õ�һ���麯��: \n";
	((func_t)*(vptr+0))();
	cout << "���õڶ����麯��: \n";
	((func_t)*(vptr+1))();
	cout << "���õ������麯��: \n";
	((func_t)*(vptr+2))();

	cout << "��һ�����ݳ�Ա�ĵ�ַ: " << endl;
	cout << &father.x << endl;
	cout << hex << (int)&father + 4 << endl;
	cout << "��һ�����ݳ�Ա��ֵ: " << endl;
	cout << dec << father.x << endl;
	cout << *(int*)((int)&father + 4) << endl;

	cout << "�ڶ������ݳ�Ա�ĵ�ַ: " << endl;
	cout << &father.y << endl;
	cout << hex << (int)&father + 8 << endl;
	cout << "�ڶ������ݳ�Ա��ֵ: " << endl;
	cout << dec << father.y << endl;
	cout << *(int*)((int)&father + 8) << endl;
	return 0;
}