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
	Student(string name = "δ����",char sex = 'f',
		int age = 0,string IDnumber = "��", CoursesGrades grades = 0.0);
	~Student();
	static void inputStudent(Student& student);			//��ʼ��
	static void addStudent(Student& student);		//���ѧ����Ϣ
	void inquireStudent();	//��ѯѧ����Ϣ

	string print() const;

private:
	unsigned int sNumber;		//ѧ��
	string name;					//����
	char sex;					//�Ա�
	int age;					//����
	string IDnumber;			//���֤��
	CoursesGrades grades;		//�ɼ�
	static int LAST_ID;			
};

