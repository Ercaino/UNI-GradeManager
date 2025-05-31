#include "../../include/gui/courses.h"
#include "../../include/gui/classes.h"
#include "../../include/gui/colors.h"
#include "../../include/gui/globals.h"
#include "../../include/gui/raygui.h"
#include "../../include/gui/utils.h"
#include "grades.h"
#include <fstream>
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>
using namespace std;

bool courseExists(const string &courseName) {
  ifstream courseFile(coursesDataPath);
  // Se il file non esiste ritorna false visto che non ci sono corsi
  if (!courseFile.is_open()) {
    return false;
  }

  string line;
  // Legge ogni riga del file, la separa in un vettore di stringhe ad ogni "," e
  // verifica se il nome del corso esiste
  while (getline(courseFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    // splitLine[0] è l'ID del corso, splitLine[1] è il nome del corso
    if (splitLine[1] == courseName) {
      return true;
    }
  }

  return false;
}

bool isValidCourseName(const string &courseName) {
  // Un nome di corso è valido se non è vuoto, ha una lunghezza compresa tra 3
  // e 50 caratteri e non contiene virgole (almeno non si rompe tutto)
  return !courseName.empty() && courseName.length() <= 50 &&
         courseName.length() >= 3 && courseName.find(',') == string::npos;
}

int writeNewCourse(const string &courseName) {
  ofstream courseFile(coursesDataPath, ios::app);
  if (!courseFile.is_open()) {
    return -1; // Error opening file
  }

  // Ottiene l'ultimo ID del corso e lo incrementa di 1 per il nuovo corso
  int lastId = getLastId(coursesDataPath);
  courseFile << to_string(lastId + 1) + "," + courseName << endl;
  return 0;
}

string listCourses() {
  ifstream coursesFile(coursesDataPath);
  string line;
  string list = "";

  while (getline(coursesFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    list += splitLine[1] += ";";
  }

  return list;
}

// Funzione per ottenere il nome del corso dato l'ID
string getCourseNameFromId(const string &courseId) {
  ifstream coursesFile(coursesDataPath);
  string line;

  while (getline(coursesFile, line)) {
    // Legge ogni riga e returna il nome del corso se l'ID corrisponde
    vector<string> splitLine = splitString(line, ',');
    if (splitLine[0] == courseId) {
      return splitLine[1];
    }
  }
  return "";
}

bool courseHasClasses(const int &courseId) {
  ifstream classesFile(classesDataPath);
  string line;

  while (getline(classesFile, line)) {
    vector<string> splitLine = splitString(line, ',');

    // Se esiste anche solo una classe con l'ID del corso, ritorna true
    if (stoi(splitLine[1]) == courseId) {
      return true;
    }
  }

  return false;
}

void drawCoursesList(Rectangle &panelRec, Rectangle &panelContentRec,
                     Vector2 &panelScroll, Rectangle &panelView) {
  GuiScrollPanel(panelRec, NULL, panelContentRec, &panelScroll, &panelView);
  BeginScissorMode(panelView.x, panelView.y, panelView.width, panelView.height);

  // Righe della tabella
  int i = 0;
  ifstream coursesFile(coursesDataPath);
  string line;

  while (getline(coursesFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    DrawRectangle(
        panelRec.x + panelScroll.x, panelRec.y + panelScroll.y + i * 60,
        panelContentRec.width - 10, 50, GetColor(sidebarBackgroundColor));

    DrawRegularText(splitLine[0], {tableOuterPadding + tableInnerPadding +
                                       regularTextPadding("ID") / 2,
                                   panelRec.y + panelScroll.y + 17 + i * 60});
    DrawRegularText(
        splitLine[1],
        {tableOuterPadding + (tableWidth - tableInnerPadding * 2) / 10,
         panelRec.y + panelScroll.y + 15 + i * 60});

    DrawRegularText(
        getCourseAverage(splitLine[0]),
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
  EndScissorMode();
}

void drawCoursesHeader() {
  DrawBoldText("ID", {tableOuterPadding + tableInnerPadding, 155});
  DrawBoldText(
      "Course name",
      {tableOuterPadding + (tableWidth - tableInnerPadding * 2) / 10, 155});
  DrawBoldText(
      "Average",
      {tableOuterPadding + (tableWidth - tableInnerPadding * 2) / 10 * 8, 155});
}
