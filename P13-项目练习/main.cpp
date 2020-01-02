#include <iostream>
#include "quickLapis.h"
#include "Warcraft.h"
#include "FixTrue.h"

void testQuickLapis() {
	quickLapis stone(100, QuickLapisLeve1::PRIMARY_LEVEL);
	cout << stone << endl;
}

void testWarcraft() {
	Warcraft warcraft(5, "����");
	cout << warcraft << endl;
}

/*�ڿ�*/
void testFixTrue() {
	FixTrue hhf("�ƺ���", "��ţ��", ImmortalLevel::LIAN_QI);
	cout << hhf << endl;

	for (size_t i = 0; i < 50; i++) {
		hhf.mining();
	}
	cout << hhf << endl;

	Warcraft warcraft(1, "����");
	hhf.fight(warcraft);
	cout << "\n����"<< warcraft << "֮��: " << endl;
	cout << hhf << endl;

	Warcraft warcraft2(1, "֩��");
	hhf.fight(warcraft2);
	Warcraft warcraft3(1, "�ڻ�");
	hhf.fight(warcraft3);
	cout << "\n����" << warcraft2 << "��" << warcraft3 <<"֮��: " << endl;
	cout << hhf << endl;

	hhf.trade(warcraft2);
	cout << "\n����" << warcraft2 << "֮��:" << endl;
	cout << hhf << endl;

	hhf.trade();
	cout << "\n������������֮��:" << endl;
	cout << hhf << endl;

	FixTrue ldm("�޶�÷", "�Ʒ��", ImmortalLevel::JIE_DAN);
	cout << ldm << endl;

	Warcraft warcraft4(2, "����");
	ldm.fight(warcraft4);
	cout << ldm << endl;

	cout << "\nó��֮��:" << endl;
	hhf.trade(ldm, warcraft4);
	cout << hhf << endl;
	cout << ldm << endl;
	cout << "---------���� trade-----------" << endl;

	Warcraft warcraft5(1, "���");
	ldm.fight(warcraft5);
	cout << ldm << endl << endl;

	hhf.trade(warcraft4, ldm, warcraft5);
	cout << hhf << endl;
	cout << ldm << endl<<endl;

	ldm.trade(warcraft4, hhf);
	cout << hhf << endl;
	cout << ldm << endl << endl;
}

int main(void) {
	testQuickLapis();
	testWarcraft();
	testFixTrue();


	system("pause");
	return 0;
}