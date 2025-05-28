#ifndef COURSES_H
#define COURSES_H
#include <string>
using namespace std;

const string coursesDataPath = "../data/courses.txt";

void addNewCourse();
void listCourses();
int chooseCourse();
bool courseHasClasses(const int &courseId);
string getCourseNameFromId(const int &courseId);

#endif
