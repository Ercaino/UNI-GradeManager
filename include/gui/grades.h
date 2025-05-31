#ifndef GRADES_H
#define GRADES_H
#include <raylib.h>
#include <string>
using namespace std;

const string gradesDataPath = "../data/grades.txt";

string getClassAverage(const string &classId);
string getCourseAverage(const string &courseId);
string getStudentAverage(const string &studentId);
void drawStudentGrades(const int &studentIndex,
                       const string &currentOpenStudentId, Rectangle &panelRec,
                       Rectangle &panelContentRec, Vector2 &panelScroll,
                       Rectangle &panelView);

#endif
