#ifndef STUDENTS_H
#define STUDENTS_H
#include <raylib.h>
#include <string>
using namespace std;

const string studentsDataPath = "../data/students.txt";

bool studentExists(const string &classId, const string &studentId);
bool isValidStudentName(const string &);
bool isValidStudentId(const string &studentId);
int getClassIdFromStudentNumber(const int &);
string getStudentIdFromStudentNumber(const int &);
string getStudentNumberFromId(const string &studentId);
bool studentHasGrades(const int &);
void drawStudentsList(Rectangle &panelRec, Rectangle &panelContentRec,
                      Vector2 &panelScroll, Rectangle &panelView,
                      int &studentIndex, string &currentOpenStudentId,
                      float &iconRotation);
void drawStudentsHeader();
int countStudentGrades(const string &studentId);
int writeNewStudent(const string &classId, const string &studentId,
                    const string &studentName);

#endif
