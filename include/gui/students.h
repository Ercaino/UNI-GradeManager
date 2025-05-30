#ifndef STUDENTS_H
#define STUDENTS_H
#include <string>
using namespace std;

const string studentsDataPath = "../data/students.txt";

void addNewStudent();
void listStudents();
string inputStudentId();
string inputStudentName();
int getClassIdFromStudentNumber(const int &);
string getStudentIdFromStudentNumber(const int &);
bool studentHasGrades(const int &);

#endif
