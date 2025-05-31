#include "../../include/gui/classes.h"
#include "../../include/gui/colors.h"
#include "../../include/gui/courses.h"
#include "../../include/gui/globals.h"
#include "../../include/gui/raygui.h"
#include "../../include/gui/students.h"
#include "../../include/gui/utils.h"
#include "grades.h"

#include <fstream>
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>
using namespace std;

bool classExists(const string &courseId, const string &className) {
  ifstream classesFile(classesDataPath);
  // Come prima, se non esiste il file non ci possono essere classi quindi
  // ritorno false
  if (!classesFile.is_open()) {
    return false;
  }

  string line;
  while (getline(classesFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    // splitLine[0] è l'ID della classe, splitLine[1] è l'ID del corso e
    // splitLine[2] è il nome della classe
    if (splitLine[1] == courseId && splitLine[2] == className) {
      return true;
    }
  }

  return false;
}

bool isValidClassName(const string &className) {
  // Un nome di classe è valido se è una singola lettera compresa tra A e Z
  return className.length() == 1 && className >= "A" && className <= "Z";
}

int writeNewClass(const string &courseId, const string &className) {
  ofstream classesFile(classesDataPath, ios::app);
  if (!classesFile.is_open()) {
    return -1;
  }

  int lastId = getLastId(classesDataPath);
  classesFile << to_string(lastId + 1) + "," + courseId + "," + className
              << endl;
  return 0;
}

// Funzione per ottenere l'ID del corso da un ID di classe
string getCourseIdFromClassId(const string &classId) {
  ifstream classesFile(classesDataPath);
  string line;

  while (getline(classesFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    if (splitLine[0] == classId) {
      return splitLine[1];
    }
  }

  return "";
}

string getClassNameFromId(const string &classId) {
  ifstream classesFile(classesDataPath);
  string line;

  while (getline(classesFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    if (splitLine[0] == classId) {
      return splitLine[2];
    }
  }

  return "";
}

bool classHasStudents(const int &classId) {
  ifstream studentsFile(studentsDataPath);
  string line;

  // Itera su ogni riga del file degli studenti, se ce n'e' almeno uno che ha
  // l'id della classe ritorna true
  while (getline(studentsFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    if (stoi(splitLine[1]) == classId) {
      return true;
    }
  }

  return false;
}

void drawClassesList(Rectangle &panelRec, Rectangle &panelContentRec,
                     Vector2 &panelScroll, Rectangle &panelView) {
  GuiScrollPanel(panelRec, NULL, panelContentRec, &panelScroll, &panelView);
  BeginScissorMode(panelView.x, panelView.y, panelView.width, panelView.height);

  // Righe della tabella
  int i = 0;
  ifstream classesFile(classesDataPath);
  string line;
  while (getline(classesFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    DrawRectangle(
        panelRec.x + panelScroll.x, panelRec.y + panelScroll.y + i * 60,
        panelContentRec.width - 10, 50, GetColor(sidebarBackgroundColor));

    DrawRegularText(
        splitLine[0].c_str(),
        {tableOuterPadding + tableInnerPadding + regularTextPadding("ID") / 2,
         panelRec.y + panelScroll.y + 17 + i * 60});
    DrawRegularText(
        getCourseNameFromId(splitLine[1]),
        {tableOuterPadding + (tableWidth - tableInnerPadding * 2) / 10,
         panelRec.y + panelScroll.y + 15 + i * 60});
    DrawRegularText(splitLine[2].c_str(),
                    {tableOuterPadding +
                         (tableWidth - tableInnerPadding * 2) / 10 * 5 +
                         boldTextPadding("Section") / 2,
                     panelRec.y + panelScroll.y + 15 + i * 60});

    DrawRegularText(
        getClassAverage(splitLine[0]),
        {tableOuterPadding + (tableWidth - tableInnerPadding * 2) / 10 * 8,
         panelRec.y + panelScroll.y + 15 + i * 60});

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
  EndScissorMode();
}

void drawClassesHeader() {
  DrawBoldText("ID", {tableOuterPadding + tableInnerPadding, 155});
  DrawBoldText(
      "Course",
      {tableOuterPadding + (tableWidth - tableInnerPadding * 2) / 10, 155});
  DrawBoldText(
      "Section",
      {tableOuterPadding + (tableWidth - tableInnerPadding * 2) / 10 * 5, 155});
  DrawBoldText(
      "Average",
      {tableOuterPadding + (tableWidth - tableInnerPadding * 2) / 10 * 8, 155});
}
