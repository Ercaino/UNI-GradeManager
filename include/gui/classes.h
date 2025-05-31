#ifndef CLASSES_H
#define CLASSES_H
#include "courses.h"
#include <raylib.h>
#include <string>
using namespace std;

const string classesDataPath = "../data/classes.txt";

bool isValidClassName(const string &);
bool classExists(const string &courseId, const string &className);
bool classHasStudents(const int &classId);
string getClassNameFromId(const string &classId);
string getCourseIdFromClassId(const string &classId);
int chooseClass(const int &mode = 1);
void drawClassesList(Rectangle &panelRec, Rectangle &panelContentRec,
                     Vector2 &panelScroll, Rectangle &panelView);
void drawClassesHeader();
int writeNewClass(const string &courseId, const string &className);

#endif
