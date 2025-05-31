#include "../../include/gui/students.h"
#include "../../include/gui/classes.h"
#include "../../include/gui/colors.h"
#include "../../include/gui/courses.h"
#include "../../include/gui/globals.h"
#include "../../include/gui/grades.h"
#include "../../include/gui/raygui.h"
#include "../../include/gui/utils.h"

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

// N.B.!!! Non confondere lo studentId con lo studentNumber, il primo e' l'id
// universitario (S7706624), il secondo e' il numero "globale" dello studente
// (1, 2, 3, ...), un id a parte che serve per il programma

bool studentExists(const string &classId, const string &studentId) {
  ifstream readStudentsFile(studentsDataPath);
  // Di nuovo, se il file non esiste non esistono studenti, quindi ritorno false
  if (!readStudentsFile.is_open()) {
    return false;
  }

  string line;
  // Leggo il file riga per riga e controllo se esiste uno studente con lo
  // stesso id, e id classe (ogni studente puo' appartenere a piu' classi)
  while (getline(readStudentsFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    if (splitLine[1] == studentId && splitLine[2] == classId) {
      return true;
    }
  }
  return false;
}

bool isValidStudentId(const string &studentId) {
  // Il formato dello studentId deve essere S7706624, quindi:
  // - Deve iniziare con 'S' o 's'
  // - Deve essere lungo 8 caratteri
  // - I restanti 7 caratteri devono essere numeri
  if (studentId.length() != 8 || (studentId[0] != 's' && studentId[0] != 'S')) {
    return false;
  }

  for (int i = 1; i < studentId.length(); i++) {
    if (!isdigit(studentId[i])) {
      return false;
    }
  }

  return true;
}

string inputStudentId() {
  cout << "Insert the student ID: ";

  string studentId;
  cin >> studentId;
  cin.ignore();

  while (!isValidStudentId(studentId)) {
    cout << "Please enter a valid ID:" << endl;
    cin >> studentId;
  }

  return studentId;
}

bool isValidStudentName(const string &studentName) {
  // Il nome dello studente non puo' essere vuoto e non puo' superare i 20
  if (studentName.length() < 4 || studentName.empty() ||
      studentName.length() > 20) {
    return false;
  }

  // Controllo che il nome contenga solo lettere e spazi
  for (char c : studentName) {
    if (!isalpha(c) && c != ' ') {
      return false;
    }
  }

  return true;
}

int writeNewStudent(const string &classId, const string &studentId,
                    const string &studentName) {
  ofstream studentsFile(studentsDataPath, ios::app);
  if (!studentsFile.is_open()) {
    return -1; // Error opening file
  }

  // Ottiene l'ultimo ID dello studente e lo incrementa di 1 per il nuovo
  // studente
  int lastId = getLastId(studentsDataPath);
  studentsFile << to_string(lastId + 1) + "," + classId + "," + studentId +
                      "," + studentName
               << endl;
  return 0;
}

int getClassIdFromStudentNumber(const int &studentNumber) {
  ifstream readStudentsFile(studentsDataPath);
  if (!readStudentsFile.is_open()) {
    return -1;
  }

  string line;
  while (getline(readStudentsFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    if (splitLine[0] == to_string(studentNumber)) {
      return stoi(splitLine[1]);
    }
  }
  return -1;
}

string getStudentIdFromStudentNumber(const int &studentNumber) {
  ifstream readStudentsFile(studentsDataPath);
  if (!readStudentsFile.is_open()) {
    return "";
  }

  string line;
  while (getline(readStudentsFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    if (splitLine[0] == to_string(studentNumber)) {
      return splitLine[2];
    }
  }
  return "";
}

string getStudentNumberFromId(const string &studentId) {
  ifstream readStudentsFile(studentsDataPath);
  if (!readStudentsFile.is_open()) {
    return "";
  }

  string line;
  while (getline(readStudentsFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    if (splitLine[2] == studentId) {
      return splitLine[0];
    }
  }
  return "";
}

bool studentHasGrades(const int &studentNumber) {
  ifstream readGradesFile(gradesDataPath);
  string gradeLine;

  while (getline(readGradesFile, gradeLine)) {
    vector<string> splitGradeLine = splitString(gradeLine, ',');

    if (stoi(splitGradeLine[2]) == studentNumber) {
      return true;
    }
  }

  return false;
}

void drawStudentsList(Rectangle &panelRec, Rectangle &panelContentRec,
                      Vector2 &panelScroll, Rectangle &panelView,
                      int &studentIndex, string &currentOpenStudentId,
                      float &iconRotation) {
  set<string> uniqueStudentIds;

  ifstream studentsFile(studentsDataPath);
  string line;
  int i = 0;

  while (getline(studentsFile, line)) {
    vector<string> splitLine = splitString(line, ',');

    if (uniqueStudentIds.find(splitLine[2]) != uniqueStudentIds.end()) {
      continue; // Skip if the student ID is already processed
    }

    uniqueStudentIds.insert(splitLine[2]);

    if (GuiButton((Rectangle){tableOuterPadding,
                              panelRec.y + panelScroll.y + i * 60,
                              tableWidth - tableInnerPadding * 4, 50},
                  NULL)) {
      if (studentIndex == i) {
        studentIndex = -1;
      } else if (getStudentAverage(splitLine[0]) != "No grades.") {
        studentIndex = i;
        currentOpenStudentId = splitLine[2];
      }
    }

    DrawRectangle(tableOuterPadding, panelRec.y + panelScroll.y + i * 60,
                  panelContentRec.width - 10, 50,
                  GetColor(sidebarBackgroundColor));

    if (studentIndex != -1) {
      DrawTextureEx(dropdownArrow,
                    {tableOuterPadding + tableInnerPadding / 3,
                     panelRec.y + panelScroll.y + 15 + i * 60},
                    iconRotation, 1, GetColor(textColor));
    } else {
      DrawTextureEx(dropdownArrowRight,
                    {tableOuterPadding + tableInnerPadding / 3,
                     panelRec.y + panelScroll.y + 15 + i * 60},
                    iconRotation, 1, GetColor(textColor));
    }

    DrawRegularText(splitLine[3], {tableOuterPadding + tableInnerPadding,
                                   panelRec.y + panelScroll.y + 15 + i * 60});

    DrawRegularText(splitLine[2],
                    {tableOuterPadding +
                         (tableWidth - tableInnerPadding * 2) / 10 * 2.5f -
                         boldTextPadding("ID") / 2,
                     panelRec.y + panelScroll.y + 15 + i * 60});

    DrawRegularText(
        getStudentAverage(splitLine[0]),
        {tableOuterPadding + (tableWidth - tableInnerPadding * 2) / 10 * 8,
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

void drawStudentsHeader() {
  DrawBoldText("Name", {tableOuterPadding + tableInnerPadding, 155});
  DrawBoldText("ID", {tableOuterPadding +
                          (tableWidth - tableInnerPadding * 2) / 10 * 2.5f,
                      155});
  DrawBoldText(
      "Average",
      {tableOuterPadding + (tableWidth - tableInnerPadding * 2) / 10 * 8, 155});
}
