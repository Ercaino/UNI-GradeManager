#ifndef COURSES_H
#define COURSES_H
#include <raylib.h>
#include <string>
using namespace std;

const string coursesDataPath = "../data/courses.txt";

bool courseExists(const string &);
bool isValidCourseName(const string &);
int writeNewCourse(const string &);
string listCourses();
bool courseHasClasses(const int &courseId);
string getCourseNameFromId(const string &courseId);
void drawCoursesList(Rectangle &panelRec, Rectangle &panelContentRec,
                     Vector2 &panelScroll, Rectangle &panelView);
void drawCoursesHeader();

#endif
