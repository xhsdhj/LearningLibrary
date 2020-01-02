#include <iostream>
#include "quickLapis.h"
#include "Warcraft.h"
#include "FixTrue.h"

void testQuickLapis() {
	quickLapis stone(100, QuickLapisLeve1::PRIMARY_LEVEL);
	cout << stone << endl;
}

void testWarcraft() {
	Warcraft warcraft(5, "òÔÁú");
	cout << warcraft << endl;
}

/*ÍÚ¿ó*/
void testFixTrue() {
	FixTrue hhf("»Æº£·å", "ÆæÅ£ÅÉ", ImmortalLevel::LIAN_QI);
	cout << hhf << endl;

	for (size_t i = 0; i < 50; i++) {
		hhf.mining();
	}
	cout << hhf << endl;

	Warcraft warcraft(1, "òÔÁú");
	hhf.fight(warcraft);
	cout << "\n²¶»ñ"<< warcraft << "Ö®ºó: " << endl;
	cout << hhf << endl;

	Warcraft warcraft2(1, "Ö©Öë");
	hhf.fight(warcraft2);
	Warcraft warcraft3(1, "±Ú»¢");
	hhf.fight(warcraft3);
	cout << "\n²¶»ñ" << warcraft2 << "ºÍ" << warcraft3 <<"Ö®ºó: " << endl;
	cout << hhf << endl;

	hhf.trade(warcraft2);
	cout << "\nÊÛÂô" << warcraft2 << "Ö®ºó:" << endl;
	cout << hhf << endl;

	hhf.trade();
	cout << "\nÊÛÂôËùÓÐÑýÊÞÖ®ºó:" << endl;
	cout << hhf << endl;

	FixTrue ldm("ÂÞ¶¬Ã·", "»Æ·ã¹È", ImmortalLevel::JIE_DAN);
	cout << ldm << endl;

	Warcraft warcraft4(2, "òÔÁú");
	ldm.fight(warcraft4);
	cout << ldm << endl;

	cout << "\nÃ³Ò×Ö®ºó:" << endl;
	hhf.trade(ldm, warcraft4);
	cout << hhf << endl;
	cout << ldm << endl;
	cout << "---------²âÊÔ trade-----------" << endl;

	Warcraft warcraft5(1, "Ìì²Ï");
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