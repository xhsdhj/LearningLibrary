#pragma once
class CoursesGrades
{
public:
	CoursesGrades(float language = 0.0, float mathematics = 0.0,
		float English = 0.0, float physics = 0.0, float chemistry = 0.0);
	~CoursesGrades();
	std::string print() const;

private:
	float language;		//语文
	float mathematics;	//数学
	float English;		//英语
	float physics;		//物理
	float chemistry;	//化学
};

