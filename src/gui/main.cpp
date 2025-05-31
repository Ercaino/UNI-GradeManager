#include "grades.h"
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "../../include/gui/classes.h"
#include "../../include/gui/colors.h"
#include "../../include/gui/courses.h"
#include "../../include/gui/globals.h"
#include "../../include/gui/loginscreen.h"
#include "../../include/gui/popups.h"
#include "../../include/gui/raygui.h"
#include "../../include/gui/sidebar.h"
#include "../../include/gui/students.h"
#include "../../include/gui/utils.h"

// Include per printf
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

// Variabili per gestire lo stato dell'applicazione
bool quit = false;
bool isPopupOpen = false;
AppState currentState = APP_STATE_LOGIN;
int studentIndex = -1;
string currentOpenStudentId = "";
float iconRotation = 0.0f;

void drawPageTitle(const string &title) {
  DrawRectangle(tableOuterPadding, 50, tableWidth, 50,
                GetColor(sidebarBackgroundColor));
  DrawRectangleLinesEx({tableOuterPadding, 50, tableWidth, 50}, 1,
                       GetColor(buttonBorderColor));
  DrawBlackText(title, {tableOuterPadding + tableInnerPadding, 50});
}

void addNewButton() {
  if (GuiButton((Rectangle){screenWidth - 90, screenHeight - 90, 35, 35},
                " ")) {
    isPopupOpen = true; // Apri il popup quando il pulsante viene cliccato
  }

  // Pulsante "+"
  DrawCircle(screenWidth - 70, screenHeight - 70, 30, BLUE);
  DrawTextureEx(
      add,
      (Vector2){(float)(float)(screenWidth - 82), (float)(screenHeight - 82)},
      0, 1, WHITE);
}

int main() {
  InitWindow(screenWidth, screenHeight, "UNI - Manage System");
  SetTargetFPS(60);

  loadResources();

  GuiSetFont(poppinsRegular);
  GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
  GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, textColor);
  GuiSetStyle(DEFAULT, BACKGROUND_COLOR, backgroundColor);
  GuiSetStyle(DEFAULT, BORDER_WIDTH, 0);
  GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, buttonBackgroundColor);
  GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, buttonBorderColor);
  GuiSetStyle(BUTTON, BORDER_WIDTH, 1);
  GuiSetStyle(TEXTBOX, BORDER_WIDTH, 1);
  GuiSetStyle(TEXTBOX, BASE_COLOR_NORMAL, sidebarBackgroundColor);
  GuiSetStyle(TEXTBOX, BASE_COLOR_DISABLED, sidebarBackgroundColor);
  GuiSetStyle(TEXTBOX, BASE_COLOR_FOCUSED, sidebarBackgroundColor);
  GuiSetStyle(TEXTBOX, BASE_COLOR_PRESSED, sidebarBackgroundColor);
  GuiSetStyle(TEXTBOX, BORDER_COLOR_NORMAL, buttonBorderColor);
  GuiSetStyle(TEXTBOX, BORDER_COLOR_DISABLED, buttonBorderColor);
  GuiSetStyle(TEXTBOX, BORDER_COLOR_FOCUSED, buttonBorderColor);
  GuiSetStyle(TEXTBOX, BORDER_COLOR_PRESSED, buttonBorderColor);

  Rectangle panelRec = {tableOuterPadding, 200, tableWidth + 15, 600};
  Rectangle panelContentRec = {tableOuterPadding, 300, tableWidth, 0};
  Rectangle panelView = {0};
  Vector2 panelScroll = {0, 0};

  Rectangle panelRecGrades = {tableOuterPadding, 200, tableWidth, 600};
  Rectangle panelContentRecGrades = {tableOuterPadding, 300, tableWidth, 0};
  Rectangle panelViewGrades = {0};
  Vector2 panelScrollGrades = {0, 0};

  Rectangle panelRecClassesPopup = {popupX + 200, popupY + 200, 315, 65};
  Rectangle panelContentRecClassesPopup = {popupX + 200, popupY + 200, 300, 0};
  Rectangle panelViewClassesPopup = {0};
  Vector2 panelScrollClassesPopup = {0, 0};

  Rectangle panelRecStudentsPopup = {popupX + 230, popupY + 260, 315, 40};
  Rectangle panelContentRecStudentsPopup = {popupX + 230, popupY + 260, 300, 0};
  Rectangle panelViewStudentsPopup = {0};
  Vector2 panelScrollStudentsPopup = {0, 0};

  while (!quit && !WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GetColor(backgroundColor));

    if (currentState == APP_STATE_LOGIN) {
      // Schermata di login
      loginScreen(currentState, quit);
    } else {
      sidebar(currentState, quit);

      // Disegno il background dell'area principale
      DrawRectangle(sidebarWidth, 0, mainAreaWidth, screenHeight,
                    GetColor(backgroundColor));

      DrawRectangle(tableOuterPadding, 150, tableWidth, 50,
                    GetColor(sidebarBackgroundColor));
      DrawRectangleLinesEx({tableOuterPadding, 150, tableWidth, 50}, 1,
                           GetColor(buttonBorderColor));

      // Disegno il pulsante + per aggiungere corsi/classi/studenti/voti
      addNewButton();
    }

    if (currentState == APP_STATE_COURSES) {
      // Area principale destra
      drawPageTitle("Courses");
      drawCoursesHeader();

      // Disegna il pannello di scroll
      panelContentRec.height = getLastId(coursesDataPath) * 60;
      drawCoursesList(panelRec, panelContentRec, panelScroll, panelView);

      popupAddCourses(isPopupOpen, quit);
    } else if (currentState == APP_STATE_CLASSES) {
      drawPageTitle("Classes");
      drawClassesHeader();

      // Disegno il pannello di scroll
      panelContentRec.height = getLastId(classesDataPath) * 60;
      if (!isPopupOpen) {
        drawClassesList(panelRec, panelContentRec, panelScroll, panelView);
      }
      popupAddClasses(isPopupOpen, quit, panelRecClassesPopup,
                      panelContentRecClassesPopup, panelViewClassesPopup,
                      panelScrollClassesPopup);
    } else if (currentState == APP_STATE_STUDENT) {
      drawPageTitle("Students and grades");
      drawStudentsHeader();
      if (studentIndex == -1) {
        panelContentRec.height = getLastId(studentsDataPath) * 60;
      } else {
        panelContentRec.height =
            (studentIndex) * 60 + countStudentGrades(currentOpenStudentId) * 60;
      }

      if (!isPopupOpen) {
        GuiScrollPanel(panelRec, NULL, panelContentRec, &panelScroll,
                       &panelView);
        BeginScissorMode(panelView.x, panelView.y, panelView.width,
                         panelView.height);
        drawStudentsList(panelRec, panelContentRec, panelScroll, panelView,
                         studentIndex, currentOpenStudentId, iconRotation);

        if (studentIndex != -1) {
          BeginScissorMode(panelView.x, panelView.y, panelView.width,
                           panelView.height);
          drawStudentGrades(studentIndex, currentOpenStudentId, panelRec,
                            panelContentRec, panelScroll, panelView);
        }
        EndScissorMode();
      }
      popupAddStudents(isPopupOpen, quit, panelRecStudentsPopup,
                       panelContentRecStudentsPopup, panelViewStudentsPopup,
                       panelScrollStudentsPopup);
    }

    EndDrawing();
  }

  UnloadTexture(logoImage);
  UnloadTexture(check);
  UnloadTexture(del);
  UnloadTexture(more);
  UnloadTexture(note);
  UnloadTexture(percent);
  UnloadTexture(add);
  CloseWindow();

  return 0;
}
