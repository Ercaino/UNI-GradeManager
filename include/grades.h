#ifndef GRADES_H
#define GRADES_H
#include <string>
using namespace std;

const string gradesDataPath = "../data/grades.txt";

int chooseStudent(bool = 1);
void addGradesToStudent();
void addGradesToClass();
void listStudentsAndGradesInAClass();
void showAverageForStudent();
void showAverageForClass();
void showAverageForCourse();

#endif
