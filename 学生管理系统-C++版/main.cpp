#include <iostream>
#include "Student.h"
#include "Database.h"

using namespace std;

/*
»Æº£·å
f
27
510183199201191913
88
66
88
77
99	
*/

int main(void) {

	Student student;
	Database database;
	database.init();

	student.addStudent(student);

	system("pause");

	return 0;
}