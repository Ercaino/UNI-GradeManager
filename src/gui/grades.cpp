#include "../../include/gui/grades.h"
#include "../../include/gui/classes.h"
#include "../../include/gui/courses.h"
#include "../../include/gui/students.h"
#include "../../include/gui/utils.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int chooseStudent(bool showingGrades) {
  int choice;
  listStudents();
  if (showingGrades) {
    cout << "Choose the student for which you want to view the average grade: ";
  } else {
    cout << "Choose the student to which you want to add grades: ";
  }

  cin >> choice;
  cin.ignore();

  while (choice < 1 || choice > getLastId(studentsDataPath)) {
    cout << "Please enter a valid student number: ";
    cin >> choice;
    cin.ignore();
  }

  return choice;
}

int inputGrade() {
  int grade;

  cin >> grade;

  while (grade > 30 || grade < 0) {
    cout << "Please enter a valid grade (0-30): ";
    cin >> grade;
  }

  return grade;
}

void addGradesToStudent() {
  const int studentNumber = chooseStudent();
  const string studentId = getStudentIdFromStudentNumber(studentNumber);

  cout << "Insert the grade for student " << studentId << ": ";
  int grade = inputGrade();
  int classId = getClassIdFromStudentNumber(studentNumber);
  int courseId = getCourseIdFromClassId(classId);

  ofstream writeGradesFile(gradesDataPath, ios::app);
  writeGradesFile << to_string(courseId) + "," + to_string(classId) + "," +
                         to_string(studentNumber) + "," + to_string(grade)
                  << endl;

  cout << "Grade added successfully for student " << studentId << "." << endl;
}

void addGradesToClass() {
  int classId = chooseClass(2);
  int courseId = getCourseIdFromClassId(classId);

  ifstream readStudentsFile(studentsDataPath);
  string studentLine;

  if (!classHasStudents(classId)) {
    cout << "There are no students in this class." << endl;
    return;
  }

  while (getline(readStudentsFile, studentLine)) {
    vector<string> splitStudentLine = splitString(studentLine, ',');

    if (stoi(splitStudentLine[1]) == classId) {
      int studentNumber = stoi(splitStudentLine[0]);
      string studentId = splitStudentLine[2];

      cout << "Insert the grade for student " << studentId << ": ";
      int grade = inputGrade();

      ofstream writeGradesFile(gradesDataPath, ios::app);
      writeGradesFile << to_string(courseId) + "," + to_string(classId) + "," +
                             to_string(studentNumber) + "," + to_string(grade)
                      << endl;

      cout << "Grade added successfully for student " << studentId << "."
           << endl;
    }
  }
}

void listStudentsAndGradesInAClass() {
  int classId = chooseClass(3);
  if (!classHasStudents(classId)) {
    cout << "There are no students in this class." << endl;
    return;
  }

  ifstream readStudentsFile(studentsDataPath);
  string studentLine;

  cout << endl << "============ Students and Grades ============" << endl;
  // Itera sul file degli studenti
  while (getline(readStudentsFile, studentLine)) {
    vector<string> splitStudentLine = splitString(studentLine, ',');

    // Controlla se lo studente appartiene alla classe scelta
    if (stoi(splitStudentLine[1]) == classId) {
      int studentNumber = stoi(splitStudentLine[0]);
      string studentId = splitStudentLine[2];

      // Controlla se lo studente ha voti
      if (!studentHasGrades(studentNumber)) {
        continue;
      }

      // Se ha voti li stampo
      cout << "Student ID: " << studentId << endl;
      cout << "    |- Grades: ";

      ifstream readGradesFile(gradesDataPath);
      string gradeLine;

      // Itera sul file dei voti
      while (getline(readGradesFile, gradeLine)) {
        vector<string> splitGradeLine = splitString(gradeLine, ',');

        // E cerco se il voto appartiene allo studente corrente
        if (stoi(splitGradeLine[2]) == studentNumber) {
          int studentNumber = stoi(splitGradeLine[2]);
          string studentId = getStudentIdFromStudentNumber(studentNumber);
          int grade = stoi(splitGradeLine[3]);

          cout << to_string(grade) + " ";
        }
      }
      cout << endl;
    }
  }
}

void showAverageForStudent() {
  int studentNumber = chooseStudent();
  if (!studentHasGrades(studentNumber)) {
    cout << "This student has no grades." << endl;
    return;
  }

  ifstream readGradesFile(gradesDataPath);
  string gradeLine;
  int totalGrades = 0;
  int numberOfGrades = 0;

  while (getline(readGradesFile, gradeLine)) {
    vector<string> splitGradeLine = splitString(gradeLine, ',');

    if (stoi(splitGradeLine[2]) == studentNumber) {
      totalGrades += stoi(splitGradeLine[3]);
      numberOfGrades++;
    }
  }

  double average = static_cast<double>(totalGrades) / numberOfGrades;
  cout << "Average grade for student "
       << getStudentIdFromStudentNumber(studentNumber) << ": " << average
       << endl;
}

void showAverageForClass() {
  int classId = chooseClass(4);
  if (!classHasStudents(classId)) {
    cout << "There are no students in this class." << endl;
    return;
  }

  ifstream readGradesFile(gradesDataPath);
  string gradeLine;
  int totalGrades = 0;
  int numberOfGrades = 0;

  while (getline(readGradesFile, gradeLine)) {
    vector<string> splitGradeLine = splitString(gradeLine, ',');

    if (stoi(splitGradeLine[1]) == classId) {
      totalGrades += stoi(splitGradeLine[3]);
      numberOfGrades++;
    }
  }

  double average = static_cast<double>(totalGrades) / numberOfGrades;
  cout << "Average grade for class ID " << classId << ": " << average << endl;
}

void showAverageForCourse() {
  int courseId = chooseCourse();
  if (!courseHasClasses(courseId)) {
    cout << "There are no classes for this course." << endl;
    return;
  }

  ifstream readGradesFile(gradesDataPath);
  string gradeLine;
  int totalGrades = 0;
  int numberOfGrades = 0;

  while (getline(readGradesFile, gradeLine)) {
    vector<string> splitGradeLine = splitString(gradeLine, ',');

    if (stoi(splitGradeLine[0]) == courseId) {
      totalGrades += stoi(splitGradeLine[3]);
      numberOfGrades++;
    }
  }

  double average = static_cast<double>(totalGrades) / numberOfGrades;
  cout << "Average grade for course ID " << courseId << ": " << average << endl;
}
