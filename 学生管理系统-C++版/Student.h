#pragma once
#include <string>
#include <vector>
#include "coursesGrades.h"

#define SITE "Student.txt"
#define NAME_MAX 32

using namespace std;

class Student
{
public:
	Student(string name = "未命名",char sex = 'f',
		int age = 0,string IDnumber = "空", CoursesGrades grades = 0.0);
	~Student();
	static void inputStudent(Student& student);			//初始化
	static void addStudent(Student& student);		//添加学生信息
	void inquireStudent();	//查询学生信息

	string print() const;

private:
	unsigned int sNumber;		//学号
	string name;					//姓名
	char sex;					//性别
	int age;					//年龄
	string IDnumber;			//身份证号
	CoursesGrades grades;		//成绩
	static int LAST_ID;			
};

