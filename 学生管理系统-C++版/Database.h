#pragma once
#include <vector>
#include "Student.h"



class Database
{
public:
	Database();
	~Database();

	//初始化,从文件中读取数据信息,来初始化用户数据
	void init();
private:
	//所有学生信息
	vector<Student> students;

	//用文件中的信息来初始化学生信息
	void initStudentsFromFile();

	//保存学生的信息到文件中
	void saveStudents();

	friend class Student;
};

