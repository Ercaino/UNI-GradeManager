#ifndef CLASSES_H
#define CLASSES_H
#include "students.h"
#include <string>
using namespace std;

const string classesDataPath = "../data/classes.txt";

void addNewClass();
void listClasses();
int getCourseIdFromClassId(const int &classId);
bool classHasStudents(const int &classId);
int chooseClass(const int &mode = 1);

#endif
