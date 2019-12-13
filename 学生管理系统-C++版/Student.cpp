#include <iostream>
#include <fstream>
#include <sstream>
#include "Student.h"
#include "Database.h"


int Student::LAST_ID = 2019000;

Student::Student(string name,char sex,
	int age, string IDnumber, CoursesGrades grades)
{
	if (name == "δ����")
	{
		this->sNumber = LAST_ID;
	}
	else {
		this->sNumber = ++LAST_ID;
	}

	this->name = name;
	this->sex = sex;
	this->age = age;
	this->IDnumber = IDnumber;
	this->grades = grades;
}



Student::~Student()
{

}

void Student::inputStudent(Student& student)
{
// 	cout << "\t\t-----ѧ������ϵͳ-----\t" << endl;
// 	cout << "\t\t1.�鿴ѧ����Ϣ\t\t" << endl;
// 	cout << "\t\t2.�޸�ѧ����Ϣ\t\t" << endl;
// 	cout << "\t\t3.ɾ��ѧ����Ϣ\t\t" << endl;
// 	cout << "\t\t4.��\t��\t\t" << endl;
	string IDnumber, name;
	char sex = NULL;
	int age = 0;
	float language = 0, mathematics = 0, English = 0, physics = 0, chemistry = 0;
	// 		cout << "������ѧ��: ";
	// 		cin >> sNumber;
	// 		if (cin.eof())
	// 		{
	// 			break;
	// 		}

	cout << "����������: ";
	cin >> name;
	int len = sizeof(name) / sizeof(name[0]);
	while (len < 0 || NAME_MAX < len || cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "��������̫��,��������������: ";
		cin >> name;
	}

	cout << "�������Ա�[f:��, m:Ů]: ";
	cin >> sex;
	while (sex != 'f' && sex != 'm' || cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "�Ա��������,�����������Ա�: ";
		cin >> sex;
	}

	cout << "����������: ";
	cin >> age;
	while (age < 0 || 150 < age || cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "�����������,��������������: ";
		cin >> age;
	}

	cout << "���������֤��: ";
	cin >> IDnumber;
	while (IDnumber.length() != 18 || cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "���֤������λ������,�������������֤��: ";
		cin >> IDnumber;
	}

	cout << "����������γ̳ɼ�[����]: ";
	cin >> language;
	while (language < 0 || 150 < language || cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "�����������,����������[����]: ";
		cin >> language;
	}

	cout << "����������γ̳ɼ�[��ѧ]: ";
	cin >> mathematics;
	while (mathematics < 0 || 150 < mathematics || cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "�����������,����������[��ѧ]: ";
		cin >> mathematics;
	}

	cout << "����������γ̳ɼ�[Ӣ��]: ";
	cin >> English;
	while (English < 0 || 150 < English || cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "�����������,����������[Ӣ��]: ";
		cin >> English;
	}

	cout << "����������γ̳ɼ�[����]: ";
	cin >> physics;
	while (physics < 0 || 150 < physics || cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "�����������,����������[����]: ";
		cin >> physics;
	}

	cout << "����������γ̳ɼ�[��ѧ]: ";
	cin >> chemistry;
	while (chemistry < 0 || 150 < chemistry || cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "�����������,����������[��ѧ]: ";
		cin >> chemistry;
	}
	student = Student(name, sex, age, IDnumber,
		CoursesGrades(language, mathematics, English, physics, chemistry));
	//student.push_back( Student(name, sex, age, IDnumber, 
		//CoursesGrades(language, mathematics, English, physics, chemistry)));
}

void Student::addStudent(Student& student)
{
	inputStudent(student);
	Database a;
	a.students.push_back(student);
	a.saveStudents();
}

string Student::print() const
{
	stringstream str;
	str << sNumber << "\t" << name << "\t"
		<< (sex == 'f'?"��":"Ů") << "\t" 
		<< age << "\t" << IDnumber << "\t" << grades.print();
	return str.str();
}
