#pragma once
class CoursesGrades
{
public:
	CoursesGrades(float language = 0.0, float mathematics = 0.0,
		float English = 0.0, float physics = 0.0, float chemistry = 0.0);
	~CoursesGrades();
	std::string print() const;

private:
	float language;		//����
	float mathematics;	//��ѧ
	float English;		//Ӣ��
	float physics;		//����
	float chemistry;	//��ѧ
};

