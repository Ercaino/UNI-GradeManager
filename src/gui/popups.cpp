#include "../../include/gui/popups.h"
#include "../../include/gui/colors.h"
#include "../../include/gui/globals.h"
#include "../../include/gui/raygui.h"

#include "../../include/gui/classes.h"
#include "../../include/gui/courses.h"
#include "../../include/gui/students.h"
#include "utils.h"

#include <cstring>
#include <fstream>
#include <raylib.h>

using namespace std;

// Variable save/delete button
bool canSave = true;
bool canDelete = true;

// Variable dropmenu
int activeOption = 0;        // Index of the currently selected option
bool dropdownActive = false; // Is the dropdown expanded?
bool focusOnId = false;

string inputCourseId = "";
string inputClassId = "";

// Variable input
char userInputAddCourses[50] = "";

char userInputAddClassesName[2] = "";
char userInputAddCourseId[50] = "";

char userInputAddStudentsName[50] = "";
char userInputAddStudentsId[9] = "";
char userInputAddClassesId[41] = "";

char userInputDeleteCourses[50] = "";
char userInputDeleteClasses[50] = "";
char userInputDeleteStudents[50] = "";

char userInputAddVoteClasses[50] = "";
char userInputAddVoteStudents[50] = "";

// Control Mouse
void controlMouse(const float &popupX, const float &popupY) {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if (CheckCollisionPointRec(
            GetMousePosition(),
            {(float)popupX + 200, (float)popupY + 130, 300, 40})) {
      focusOnId = false; // Focus on "Name" text box
    } else if (CheckCollisionPointRec(
                   GetMousePosition(),
                   {(float)popupX + 200, (float)popupY + 210, 300, 40})) {
      focusOnId = true; // Focus on "ID" text box
    }
  }
}

// BeginPopUP
void popup(const string &title) {
  // Dim schermo
  DrawRectangle(0, 0, screenWidth, screenHeight, GetColor(coverColor));

  // Disegna il rettangolo del popup
  DrawRectangle(popupX, popupY, popupWidth, popupHeight, GetColor(popUpBack));
  DrawRectangleLines(popupX, popupY, popupWidth, popupHeight, BLACK);

  // Disegna barra
  DrawRectangle(popupX, popupY, popupWidth, popupHeight / 4 - 10,
                GetColor(popUpBar));
  DrawBoldText(title, {popupX + 30, popupY + 35});
}

// Button for esc popup
void buttonEsc(bool &isPopupOpen) {
  // Pulsante "Chiudi" nel popup
  if (GuiButton((Rectangle){popupX + 350, popupY + 340, 100, 40}, "ESC")) {
    isPopupOpen = false; // Chiudi il popup
  }
}

// Button add
void popupAddCourses(bool &isPopupOpen, bool &quit) {
  // Disegna il popup se è aperto
  if (isPopupOpen) {
    popup("Add Courses");

    // Testo nel popup
    DrawText("Course Name", popupX + 30, popupY + 140, 20, GetColor(textColor));
    GuiTextBox({(float)popupX + 200, (float)popupY + 130, 300, 40},
               userInputAddCourses, 50, true);

    // Pulsante "Chiudi" nel popup
    buttonEsc(isPopupOpen);
    string str(userInputAddCourses, 50);

    if (courseExists(userInputAddCourses) ||
        !isValidCourseName(userInputAddCourses)) {
      if (courseExists(userInputAddCourses))
        DrawText("Course already exists", popupX + 30, popupY + 200, 20, RED);

      if (!isValidCourseName(userInputAddCourses))
        DrawText("Invalid name. (3-50 char)", popupX + 30, popupY + 200, 20,
                 RED);

      canSave = false;
    } else
      canSave = true;

    // Pulsante "Salva" nel popup
    if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40}, "Save")) {
      if (canSave) {
        writeNewCourse(userInputAddCourses);
        strcpy(userInputAddCourses, "");
        isPopupOpen = false; // Chiudi il popup
      }
    }
  }
}

void popupAddClasses(bool &isPopupOpen, bool &quit, Rectangle &panelRec,
                     Rectangle &panelContentRec, Rectangle &panelView,
                     Vector2 &panelScroll) {
  // Disegna il popup se è aperto
  if (isPopupOpen) {
    popup("Add Classes");

    // Testo nel popup
    // Name
    DrawBoldText("Class name", {popupX + 30, popupY + 140});
    GuiTextBox({popupX + 200, popupY + 140, 300, 40}, userInputAddClassesName,
               2, !focusOnId);
    // DropDown Course
    DrawBoldText("In Course", {popupX + 30, popupY + 200});

    int i = 0;
    ifstream coursesFile(coursesDataPath);
    string line;

    if (dropdownActive) {
      panelContentRec.height = getLastId(coursesDataPath) * 30;
      GuiScrollPanel(panelRec, NULL, panelContentRec, &panelScroll, &panelView);
      BeginScissorMode(panelView.x, panelView.y, panelView.width,
                       panelView.height);
      while (getline(coursesFile, line)) {
        vector<string> splitLine = splitString(line, ',');
        if (GuiButton({panelRec.x + panelScroll.x,
                       panelRec.y + panelScroll.y + i * 30,
                       panelContentRec.width, 30},
                      NULL)) {
          inputCourseId = splitLine[0];
          dropdownActive = false;
        }
        DrawRectangle(
            panelRec.x + panelScroll.x, panelRec.y + panelScroll.y + i * 30,
            panelContentRec.width, 30, GetColor(sidebarBackgroundColor));
        DrawLineEx({panelRec.x + panelScroll.x + 10,
                    panelRec.y + panelScroll.y + i * 30},
                   {panelRec.x + panelContentRec.width - 10,
                    panelRec.y + panelScroll.y + i * 30},
                   1, GetColor(buttonBorderColor));

        DrawRegularText(splitLine[1],
                        {panelRec.x + panelScroll.x + 10,
                         panelRec.y + panelScroll.y + 5 + i * 30});
        i++;
      }
      EndScissorMode();
    } else {
      if (GuiButton({panelRec.x, panelRec.y, panelContentRec.width, 40},
                    NULL)) {
        dropdownActive = true;
      }
      DrawRectangle(panelRec.x, panelRec.y, panelContentRec.width, 40,
                    GetColor(sidebarBackgroundColor));
      DrawRectangleLinesEx({panelRec.x, panelRec.y, panelContentRec.width, 40},
                           1, GetColor(buttonBorderColor));
      DrawRegularText(getCourseNameFromId(inputCourseId),
                      {popupX + 210, popupY + 210});
    }

    // Control mouse
    controlMouse(popupX, popupY);

    // Pulsante "Chiudi" nel popup
    buttonEsc(isPopupOpen);

    string className(userInputAddClassesName);

    if (classExists(inputCourseId, className)) {
      DrawBoldText("Course already exists", {popupX + 30, popupY + 275},
                   boldFontSize, errorColor);
      canSave = false;
    } else if (!isValidClassName(className)) {
      DrawBoldText("Invalid name. (max. 1 char. A-Z)",
                   {popupX + 30, popupY + 275}, boldFontSize, errorColor);
      canSave = false;
    } else {
      canSave = true;
    }

    // Pulsante "Salva" nel popup
    if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40}, "Save")) {
      if (canSave) {
        writeNewClass(inputCourseId, className);
        strcpy(userInputAddClassesName, "");
        strcpy(userInputAddCourseId, "");
        isPopupOpen = false; // Chiudi il popup
      }
    }
  }
}

void popupAddStudents(bool &isPopupOpen, bool &quit, Rectangle &panelRec,
                      Rectangle &panelContentRec, Rectangle &panelView,
                      Vector2 &panelScroll) {
  // Disegna il popup se è aperto
  if (isPopupOpen) {
    popup("Add Students");

    // Testo nel popup
    // DropDown Course and Class
    DrawBoldText("Class", {popupX + 30, popupY + 260});

    // Name and Id Student
    DrawBoldText("Student Name", {popupX + 30, popupY + 120});
    GuiTextBox({popupX + 230, popupY + 120, 300, 40}, userInputAddStudentsName,
               50, !focusOnId);
    DrawBoldText("Student Id", {popupX + 30, popupY + 190});
    GuiTextBox({popupX + 230, popupY + 190, 300, 40}, userInputAddStudentsId,
               50, focusOnId);

    panelContentRec.height = getLastId(classesDataPath) * 40;

    int i = 0;
    ifstream classesFile(classesDataPath);
    string line;

    if (dropdownActive) {
      GuiScrollPanel(panelRec, NULL, panelContentRec, &panelScroll, &panelView);
      BeginScissorMode(panelView.x, panelView.y, panelView.width,
                       panelView.height);
      while (getline(classesFile, line)) {
        vector<string> splitLine = splitString(line, ',');
        if (GuiButton({panelRec.x + panelScroll.x,
                       panelRec.y + panelScroll.y + i * 40,
                       panelContentRec.width, 40},
                      NULL)) {
          inputClassId = splitLine[0];
          inputCourseId = splitLine[1];
          dropdownActive = false;
        }
        DrawRectangle(
            panelRec.x + panelScroll.x, panelRec.y + panelScroll.y + i * 40,
            panelContentRec.width, 40, GetColor(sidebarBackgroundColor));
        DrawLineEx({panelRec.x + panelScroll.x + 10,
                    panelRec.y + panelScroll.y + i * 40},
                   {panelRec.x + panelContentRec.width - 10,
                    panelRec.y + panelScroll.y + i * 40},
                   1, GetColor(buttonBorderColor));

        DrawRegularText(getCourseNameFromId(splitLine[1]) + " section " +
                            splitLine[2],
                        {panelRec.x + panelScroll.x + 10,
                         panelRec.y + panelScroll.y + 5 + i * 40});
        i++;
      }
      EndScissorMode();
    } else {
      if (GuiButton({panelRec.x, panelRec.y, panelContentRec.width, 40},
                    NULL)) {
        dropdownActive = true;
      }
      DrawRectangle(panelRec.x, panelRec.y, panelContentRec.width, 40,
                    GetColor(sidebarBackgroundColor));
      DrawRectangleLinesEx({panelRec.x, panelRec.y, panelContentRec.width, 40},
                           1, GetColor(buttonBorderColor));
      DrawRegularText(getCourseNameFromId(inputCourseId) + " section " +
                          getClassNameFromId(inputClassId),
                      {popupX + 240, popupY + 265});
    }

    // Controll mouse
    controlMouse(popupX, popupY);

    // Pulsante "Chiudi" nel popup
    buttonEsc(isPopupOpen);

    string studentId(userInputAddStudentsId);
    string studentName(userInputAddStudentsName);

    if (!isValidStudentId(studentId)) {
      DrawText("Invalid Student ID", popupX + 30, popupY + 340, 20, RED);
      canSave = false;
    }

    else if (studentExists(inputClassId, studentId)) {
      DrawText("Student already exists", popupX + 30, popupY + 340, 20, RED);
      canSave = false;
    }

    else if (!isValidStudentName(studentName)) {
      DrawText("Invalid name. (4-50 char)", popupX + 30, popupY + 340, 20, RED);
      canSave = false;
    } else {
      canSave = true;
    }

    // Pulsante "Salva" nel popup
    if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40}, "Save")) {
      if (canSave) {
        writeNewStudent(inputClassId, studentId, studentName);
        // userInputAddClassesName = "";
        strcpy(userInputAddClassesName, "");
        strcpy(userInputAddStudentsId, "");
        isPopupOpen = false; // Chiudi il popup
      }
    }
  }
}

// Button add icon
void popupAddIconClasses(bool &isPopupOpen, bool &quit) {
  // Disegna il popup se è aperto
  if (isPopupOpen) {
    const char *title = "Add Classes";
    popup(title);

    // Testo nel popup
    // Name
    DrawText("Classes Name", popupX + 30, popupY + 140, 20,
             GetColor(textColor));
    GuiTextBox({(float)popupX + 200, (float)popupY + 130, 300, 40},
               userInputAddClassesName, 255, !focusOnId);

    // Control mouse
    controlMouse(popupX, popupY);

    // Pulsante "Chiudi" nel popup
    buttonEsc(isPopupOpen);

    string userInputAddClassesName(userInputAddClassesName, 50);

    if (classExists(userInputAddCourseId, userInputAddClassesName) ||
        !isValidClassName(userInputAddClassesName)) {
      if (classExists(userInputAddCourseId, userInputAddClassesName))
        DrawText("Course already exists", popupX + 30, popupY + 275, 20, RED);

      if (!isValidClassName(userInputAddClassesName))
        DrawText("Invalid name. (3-50 char)", popupX + 30, popupY + 275, 20,
                 RED);

      canSave = false;
    } else
      canSave = true;

    // Pulsante "Salva" nel popup
    if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40}, "Save")) {
      if (canSave) {
        writeNewClass(userInputAddCourseId, userInputAddClassesName);
        // strcpy(userInputAddClassesName, "");
        // userInputAddCourseId = 0;
        isPopupOpen = false; // Chiudi il popup
      }
    }
  }
}

void popupAddIconStudents(bool &isPopupOpen, bool &quit) {
  // Disegna il popup se è aperto
  if (isPopupOpen) {
    const char *title = "Add Students";
    popup(title);

    // Testo nel popup
    // DropDown Course and Class
    DrawText("In Course", popupX + 30, popupY + 270, 20, GetColor(textColor));

    // Name and Id Student
    DrawText("Students Name", popupX + 30, popupY + 140, 20,
             GetColor(textColor));
    GuiTextBox({(float)popupX + 200, (float)popupY + 130, 300, 40},
               userInputAddStudentsName, 255, !focusOnId);
    DrawText("Students Id", popupX + 30, popupY + 210, 20, GetColor(textColor));
    GuiTextBox({(float)popupX + 200, (float)popupY + 200, 300, 40},
               userInputAddStudentsId, 255, !focusOnId);

    // Controll mouse
    controlMouse(popupX, popupY);

    // Pulsante "Chiudi" nel popup
    buttonEsc(isPopupOpen);

    string userInputAddClassesName(userInputAddClassesName, 50);
    string userInputAddStudentsId(userInputAddStudentsId, 50);

    if (!isValidStudentId(userInputAddStudentsId)) {
      DrawText("Invalid Student ID", popupX + 30, popupY + 340, 20, RED);
      canSave = false;
    } else if (studentExists(userInputAddClassesId, userInputAddStudentsId) ||
               !isValidStudentName(userInputAddClassesName)) {
      if (studentExists(userInputAddStudentsId, userInputAddClassesName))
        DrawText("Student already exists", popupX + 30, popupY + 340, 20, RED);

      if (!isValidStudentName(userInputAddClassesName))
        DrawText("Invalid name. (3-50 char)", popupX + 30, popupY + 340, 20,
                 RED);

      canSave = false;
    } else
      canSave = true;

    // Pulsante "Save" nel popup
    if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40}, "Save")) {
      if (canSave) {
        writeNewStudent(userInputAddClassesId, userInputAddStudentsId,
                        userInputAddClassesName);
        userInputAddClassesName = "";
        userInputAddStudentsId = "";
        isPopupOpen = false; // Chiudi il popup
      }
    }
  }
}

// Button Delete
void popupDeleteCourses(bool &isPopupOpen, bool &quit) {
  // Disegna il popup se è aperto
  if (isPopupOpen) {
    const char *title = "Delete Courses";
    popup(title);

    DrawText("Are you sure", popupX + 30, popupY + 140, 20,
             GetColor(textColor));

    // variabile da usare userInputDeleteCourses

    // Pulsante "Chiudi" nel popup
    buttonEsc(isPopupOpen);

    // Pulsante "Delete" nel popup
    if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40}, "Delete")) {
      if (canDelete) {
        // funzione elimina
        strcpy(userInputDeleteCourses, "");
        isPopupOpen = false; // Chiudi il popup
      }
    }
  }
}
void popupDeleteClasses(bool &isPopupOpen, bool &quit) {
  // Disegna il popup se è aperto
  if (isPopupOpen) {
    const char *title = "Delete Classes";
    popup(title);

    DrawText("Are you sure", popupX + 30, popupY + 140, 20,
             GetColor(textColor));

    // variabile da usare userInputDeleteClasses

    // Pulsante "Chiudi" nel popup
    buttonEsc(isPopupOpen);

    // Pulsante "Delete" nel popup
    if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40}, "Delete")) {
      if (canDelete) {
        // funzione elimina
        strcpy(userInputDeleteClasses, "");
        isPopupOpen = false; // Chiudi il popup
      }
    }
  }
}
void popupDeleteStudents(bool &isPopupOpen, bool &quit) {
  // Disegna il popup se è aperto
  if (isPopupOpen) {
    const char *title = "Delete Students";
    popup(title);

    DrawText("Are you sure", popupX + 30, popupY + 140, 20,
             GetColor(textColor));

    // variabile da usare userInputDeleteStudents

    // Pulsante "Chiudi" nel popup
    buttonEsc(isPopupOpen);

    // Pulsante "Delete" nel popup
    if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40}, "Delete")) {
      if (canDelete) {
        // funzione elimina
        strcpy(userInputDeleteStudents, "");
        isPopupOpen = false; // Chiudi il popup
      }
    }
  }
}

// Button Edit
// void popupEditCourses(bool &isPopupOpen, bool &quit);
// void popupEditClasses(bool &isPopupOpen, bool &quit);
// void popupEditStudents(bool &isPopupOpen, bool &quit);

// Add Vote
void popupAddVoteClasses(bool &isPopupOpen, bool &quit) {
  // Disegna il popup se è aperto
  if (isPopupOpen) {
    const char *title = "Add Vote";
    popup(title);

    // Testo nel popup
    DrawText("Vote out of thirty, for the entire Classes", popupX + 30,
             popupY + 140, 20, GetColor(textColor));
    DrawText("Vote", popupX + 30, popupY + 210, 20, GetColor(textColor));
    GuiTextBox({(float)popupX + 200, (float)popupY + 130, 300, 40},
               userInputAddVoteClasses, 255, true);

    // variabile da usare userInputAddVoteClasses

    // Pulsante "Chiudi" nel popup
    buttonEsc(isPopupOpen);

    // Pulsante "Save" nel popup
    if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40}, "Save")) {
      if (canSave) {
        // funzione voto insert Classes
        strcpy(userInputAddVoteClasses, "");
        isPopupOpen = false; // Chiudi il popup
      }
    }
  }
}
void popupAddVoteStudents(bool &isPopupOpen, bool &quit) {
  // Disegna il popup se è aperto
  if (isPopupOpen) {
    const char *title = "Add Vote Students";
    popup(title);

    // Testo nel popup
    DrawText("Vote out of thirty, for the entire Students", popupX + 30,
             popupY + 140, 20, GetColor(textColor));
    DrawText("Vote", popupX + 30, popupY + 210, 20, GetColor(textColor));
    GuiTextBox({(float)popupX + 200, (float)popupY + 130, 300, 40},
               userInputAddVoteStudents, 255, true);

    // variabile da usare userInputAddVoteStudents

    // Pulsante "Chiudi" nel popup
    buttonEsc(isPopupOpen);

    // Pulsante "Save" nel popup
    if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40}, "Save")) {
      if (canSave) {
        // funzione voto insert Students
        strcpy(userInputAddVoteStudents, "");
        isPopupOpen = false; // Chiudi il popup
      }
    }
  }
}
