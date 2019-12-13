#include <iostream>
#include <sstream>
#include <string>
#include "coursesGrades.h"


CoursesGrades::CoursesGrades(float language, float mathematics,
	float English, float physics, float chemistry)
{
	this->language = language;
	this->mathematics = mathematics;
	this->English = English;
	this->physics = physics;
	this->chemistry = chemistry;
}

CoursesGrades::~CoursesGrades()
{
}

std::string CoursesGrades::print() const
{
	std::stringstream str;
	str << language << "\t" << mathematics << "\t"
		<< English << "\t" << physics << "\t"
		<< chemistry << "\t";
	return str.str();
}

