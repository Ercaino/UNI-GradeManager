#include "../../include/gui/grades.h"
#include "../../include/gui/raygui.h"
#include "../../include/gui/utils.h"
#include "classes.h"
#include "courses.h"
#include "students.h"
#include <fstream>
#include <iostream>
#include <raylib.h>
#include <sstream>
#include <string>
using namespace std;

bool isValidGrade(const string &grade) {
  istringstream stream(grade);
  string word;

  while (stream >> word) {
    // Check if the word is a number
    bool isNumber = true;
    for (char c : word) {
      if (!isdigit(c)) {
        isNumber = false;
        break;
      }
    }

    if (isNumber) {
      // Convert the word to an integer
      int number = stoi(word);

      // Check if the number is in the range [0, 30]
      if (number >= 0 && number <= 30) {
        return true; // Valid number found
      }
    }
  }

  return false; // No valid number found
}

string getCourseAverage(const string &courseId) {
  ifstream gradesFile(gradesDataPath);
  string line;
  int totalGrades = 0;
  double numberOfGrades = 0;

  while (getline(gradesFile, line)) {
    vector<string> splitLine = splitString(line, ',');

    if (splitLine[0] == courseId) {
      totalGrades += stoi(splitLine[3]);
      numberOfGrades++;
    }
  }

  if (numberOfGrades == 0) {
    return "No grades.";
  }

  double average = totalGrades / numberOfGrades;
  ostringstream oss;
  oss.precision(2);
  oss << fixed << average;
  return oss.str();
}

string getClassAverage(const string &classId) {
  ifstream gradesFile(gradesDataPath);
  string line;
  double totalGrades = 0;
  int numberOfGrades = 0;

  while (getline(gradesFile, line)) {
    vector<string> splitLine = splitString(line, ',');

    if (splitLine[1] == classId) {
      totalGrades += stoi(splitLine[3]);
      numberOfGrades++;
    }
  }

  if (numberOfGrades == 0) {
    return "No grades.";
  }

  double average = static_cast<double>(totalGrades) / numberOfGrades;
  ostringstream oss;
  oss.precision(2);
  oss << fixed << average;
  return oss.str();
}

string getStudentAverage(const string &studentId) {
  ifstream gradesFile(gradesDataPath);
  string line;
  double totalGrades = 0;
  int numberOfGrades = 0;

  while (getline(gradesFile, line)) {
    vector<string> splitLine = splitString(line, ',');

    if (splitLine[2] == studentId) {
      totalGrades += stoi(splitLine[3]);
      numberOfGrades++;
    }
  }

  if (numberOfGrades == 0) {
    return "No grades.";
  }

  double average = static_cast<double>(totalGrades) / numberOfGrades;
  ostringstream oss;
  oss.precision(2);
  oss << fixed << average;
  return oss.str();
}

int countStudentGrades(const string &studentId) {
  ifstream gradesFile(gradesDataPath);
  string line;
  int count = 0;

  while (getline(gradesFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    if (splitLine[2] == getStudentNumberFromId(studentId)) {
      count++;
    }
  }

  return count;
}

void drawStudentGrades(const int &studentIndex,
                       const string &currentOpenStudentId, Rectangle &panelRec,
                       Rectangle &panelContentRec, Vector2 &panelScroll,
                       Rectangle &panelView) {

  ifstream gradesFile(gradesDataPath);
  string line;
  int i = studentIndex + 1;

  while (getline(gradesFile, line)) {
    vector<string> splitLine = splitString(line, ',');

    if (splitLine[2] != getStudentNumberFromId(currentOpenStudentId)) {
      continue; // Skip if the student ID does not match
    }

    DrawRectangle(tableOuterPadding, panelRec.y + panelScroll.y + i * 60,
                  panelContentRec.width - 10, 50,
                  GetColor(sidebarBackgroundColor));

    DrawRegularText("Course: " + getCourseNameFromId(splitLine[0]),
                    {tableOuterPadding + tableInnerPadding,
                     panelRec.y + panelScroll.y + 15 + i * 60});

    DrawRegularText("Section: " + getClassNameFromId(splitLine[1]),
                    {tableOuterPadding +
                         (tableWidth - tableInnerPadding * 2) / 10 * 2.5f -
                         boldTextPadding("ID") / 2,
                     panelRec.y + panelScroll.y + 15 + i * 60});

    DrawRegularText(
        "Grade: " + splitLine[3],
        {tableOuterPadding + (tableWidth - tableInnerPadding * 2) / 10 * 4,
         panelRec.y + panelScroll.y + 15 + i * 60});

    // Icone di modifica e eliminazione
    DrawTextureEx(note,
                  {tableOuterPadding + (tableWidth - tableInnerPadding * 2) -
                       (tableWidth - tableInnerPadding) / 20,
                   panelRec.y + panelScroll.y + 15 + i * 60},
                  0, 1, GetColor(textColor));
    DrawTextureEx(del,
                  {tableOuterPadding + (tableWidth - tableInnerPadding * 2),
                   panelRec.y + panelScroll.y + 15 + i * 60},
                  0, 1, GetColor(textColor));
    i++;
  }
}
