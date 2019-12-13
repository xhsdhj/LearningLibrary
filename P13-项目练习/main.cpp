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

void testFixTrue() {
	FixTrue hhf("»Æº£·å", "ÆæÅ£ÅÉ", ImmortalLevel::LIAN_QI);
	cout << hhf << endl;

	for (size_t i = 0; i < 50; i++) {
		hhf.mining();
	}
	cout << hhf << endl;
}

int main(void) {
	testQuickLapis();
	testWarcraft();
	testFixTrue();


	system("pause");
	return 0;
}