#include <iostream>
#include <fstream>
#include <sstream>
#include "Student.h"
#include "Database.h"


int Student::LAST_ID = 2019000;

Student::Student(string name,char sex,
	int age, string IDnumber, CoursesGrades grades)
{
	if (name == "未命名")
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
// 	cout << "\t\t-----学生管理系统-----\t" << endl;
// 	cout << "\t\t1.查看学生信息\t\t" << endl;
// 	cout << "\t\t2.修改学生信息\t\t" << endl;
// 	cout << "\t\t3.删除学生信息\t\t" << endl;
// 	cout << "\t\t4.退\t出\t\t" << endl;
	string IDnumber, name;
	char sex = NULL;
	int age = 0;
	float language = 0, mathematics = 0, English = 0, physics = 0, chemistry = 0;
	// 		cout << "请输入学号: ";
	// 		cin >> sNumber;
	// 		if (cin.eof())
	// 		{
	// 			break;
	// 		}

	cout << "请输入姓名: ";
	cin >> name;
	int len = sizeof(name) / sizeof(name[0]);
	while (len < 0 || NAME_MAX < len || cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "名字输入太长,请重新输入名字: ";
		cin >> name;
	}

	cout << "请输入性别[f:男, m:女]: ";
	cin >> sex;
	while (sex != 'f' && sex != 'm' || cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "性别输入错误,请重新输入性别: ";
		cin >> sex;
	}

	cout << "请输入年龄: ";
	cin >> age;
	while (age < 0 || 150 < age || cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "年龄输入错误,请重新输入年龄: ";
		cin >> age;
	}

	cout << "请输入身份证号: ";
	cin >> IDnumber;
	while (IDnumber.length() != 18 || cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "身份证号输入位数错误,请重新输入身份证号: ";
		cin >> IDnumber;
	}

	cout << "请依次输入课程成绩[语文]: ";
	cin >> language;
	while (language < 0 || 150 < language || cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "分数输入错误,请重新输入[语文]: ";
		cin >> language;
	}

	cout << "请依次输入课程成绩[数学]: ";
	cin >> mathematics;
	while (mathematics < 0 || 150 < mathematics || cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "分数输入错误,请重新输入[数学]: ";
		cin >> mathematics;
	}

	cout << "请依次输入课程成绩[英语]: ";
	cin >> English;
	while (English < 0 || 150 < English || cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "分数输入错误,请重新输入[英语]: ";
		cin >> English;
	}

	cout << "请依次输入课程成绩[物理]: ";
	cin >> physics;
	while (physics < 0 || 150 < physics || cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "分数输入错误,请重新输入[物理]: ";
		cin >> physics;
	}

	cout << "请依次输入课程成绩[化学]: ";
	cin >> chemistry;
	while (chemistry < 0 || 150 < chemistry || cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "分数输入错误,请重新输入[化学]: ";
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
		<< (sex == 'f'?"男":"女") << "\t" 
		<< age << "\t" << IDnumber << "\t" << grades.print();
	return str.str();
}
