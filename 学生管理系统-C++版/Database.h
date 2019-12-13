#pragma once
#include <vector>
#include "Student.h"



class Database
{
public:
	Database();
	~Database();

	//��ʼ��,���ļ��ж�ȡ������Ϣ,����ʼ���û�����
	void init();
private:
	//����ѧ����Ϣ
	vector<Student> students;

	//���ļ��е���Ϣ����ʼ��ѧ����Ϣ
	void initStudentsFromFile();

	//����ѧ������Ϣ���ļ���
	void saveStudents();

	friend class Student;
};

