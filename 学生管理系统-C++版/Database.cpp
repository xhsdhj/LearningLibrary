#include <iostream>
#include <fstream>
#include "Database.h"

Database::Database()
{
}

Database::~Database()
{
}

void Database::init()
{
	initStudentsFromFile();
}

void Database::initStudentsFromFile()
{
	ifstream stream;
	stream.open(SITE);

	if (!stream.is_open()) {
		cout << "û��ѧ����Ϣ!����ӳ�ʼ��Ϣ!" << endl;
		Student student;
		Student::inputStudent(student);
		students.push_back(student);
		saveStudents();
		stream.close();
		return;
	}

	while (1)
	{
		unsigned int sNumber;
		string IDnumber, line, name, gender;
		char sex = NULL;
		int age=0;
		float language=0, mathematics=0, English=0, physics=0, chemistry=0;

		//getline(stream, line);	//��ȡһ������
		if (stream.eof())
		{
			break;
		}

		stream >> sNumber >> name >> gender >> age >> IDnumber
			>> language >> mathematics >> English >> physics >> chemistry;
		sex = gender == "��" ? 'f' : 'm';

// 		int ret = sscanf_s(line.c_str(), "%d %s %c %d %s %f %f %f %f %f",
// 			&sNumber, name, sizeof(name), &sex, sizeof(sex), &age, IDnumber,
// 			&language, &mathematics, &English, &physics, &chemistry);

// 		if (ret <= 0)
// 		{
// 			cout << "��������ݸ�ʽ����ȷ!����ʧ��!" << endl;
// 			system("pause");
// 			exit(1);
// 		}
		//���������ѧ����Ϣ
		students.push_back(Student(name, sex, age, IDnumber, 
			CoursesGrades(language, mathematics, English, physics, chemistry)));
	}
	stream.close();
}

void Database::saveStudents()
{
	ofstream stream;
	stream.open(SITE);
	if (!stream.is_open())
	{
		cout << SITE << "д��ʧ��!" << endl;
		exit(1);
	}
	for (int i = 0; i < students.size(); i++)
	{
		stream << students[i].print() << endl;
	}
	stream.close();
}
