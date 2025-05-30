#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "../../include/gui/classes.h"
#include "../../include/gui/colors.h"
#include "../../include/gui/courses.h"
#include "../../include/gui/globals.h"
#include "../../include/gui/loginscreen.h"
#include "../../include/gui/raygui.h"
#include "../../include/gui/sidebar.h"
#include "../../include/gui/students.h"
#include "../../include/gui/utils.h"

// Include per printf
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Variabili per gestire lo stato dell'applicazione
bool quit = false;
bool isPopupOpen = false;
bool canSave = true;
AppState currentState = APP_STATE_LOGIN;

void mainArea(const char *section) {
  DrawRectangle((float)(screenWidth / 3), 0, (float)(1100), screenHeight,
                GetColor(backgroundColor));

  // Tabella dei corsi
  DrawRectangle((float)(screenWidth / 3 + 75), 50,
                (float)(screenWidth / 2 + 100), 30, GREEN);
  DrawText(section, (float)(screenWidth / 3 + 100), 55, 20, WHITE);
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

void DrawCustomText(const string &text, Vector2 position, float fontSize = 20) {
  DrawTextEx(customfont, text.c_str(), position, fontSize, 1,
             GetColor(textColor));
};

int main() {
  InitWindow(screenWidth, screenHeight, "UNI - Manage System");
  SetTargetFPS(60);

  loadResources();

  GuiSetFont(customfont);
  GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
  GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, textColor);
  GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, buttonBackgroundColor);
  GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, buttonBorderColor);

  char userInput[256] = "";

  while (!quit && !WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(GetColor(backgroundColor));

    if (currentState == APP_STATE_LOGIN) {
      // Schermata di login
      loginScreen(currentState, quit);
    } else if (currentState == APP_STATE_COURSES) {
      // Barra laterale sinistra
      sidebar(currentState, quit);

      // Area principale destra
      mainArea("Courses");

      // Disegna il pulsante "+"
      addNewButton();

      // Righe della tabella
      int i = 0;
      ifstream coursesFile(coursesDataPath);
      string line;
      while (getline(coursesFile, line)) {
        vector<string> splitLine = splitString(line, ',');
        i++;
        DrawRectangle((float)(screenWidth / 3 + 75), 90 + i * 60,
                      (float)(screenWidth / 2 + 100), 50,
                      GetColor(sidebarBackgroundColor));
        DrawCustomText("Course name:",
                       {float(screenWidth / 3 + 100), float(100 + i * 60)});
        DrawCustomText(splitLine[1],
                       {float(screenWidth / 3 + 250), float(100 + i * 60)});
        DrawCustomText("ID",
                       {(float)(screenWidth / 3 + 700), (float)(100 + i * 60)});
        DrawCustomText(splitLine[0],
                       {(float)(screenWidth / 3 + 750), (float)(100 + i * 60)});

        // Icone di modifica e eliminazione
        DrawTextureEx(
            percent,
            (Vector2){(float)(screenWidth / 3 + 850), (float)(100 + i * 60)}, 0,
            1, GetColor(textColor));
        DrawTextureEx(
            del,
            (Vector2){(float)(screenWidth / 3 + 900), (float)(100 + i * 60)}, 0,
            1, GetColor(textColor));
        DrawTextureEx(
            more,
            (Vector2){(float)(screenWidth / 3 + 950), (float)(100 + i * 60)}, 0,
            1, GetColor(textColor));
      }

      // Disegna il popup se è aperto
      if (isPopupOpen) {
        // Dimensioni e posizione del popup
        int popupWidth = 600;
        int popupHeight = 400;
        int popupX = screenWidth / 2 - popupWidth / 2;
        int popupY = screenHeight / 2 - popupHeight / 2;

        // Dim schermo
        DrawRectangle(0, 0, screenWidth, screenHeight, GetColor(coverColor));

        // Disegna il rettangolo del popup
        DrawRectangle(popupX, popupY, popupWidth, popupHeight,
                      GetColor(popUpBack));
        DrawRectangleLines(popupX, popupY, popupWidth, popupHeight, BLACK);

        // Disegna barra
        DrawRectangle(popupX, popupY, popupWidth, popupHeight / 4 - 10,
                      GetColor(popUpBar));
        DrawText("ADD Courses", popupX + 30, popupY + 35, 20,
                 GetColor(textColor));

        // Testo nel popup
        DrawText("Course Name", popupX + 30, popupY + 140, 20,
                 GetColor(textColor));
        GuiTextBox({(float)popupX + 200, (float)popupY + 130, 300, 40},
                   userInput, 255, true);

        // Pulsante "Chiudi" nel popup
        if (GuiButton((Rectangle){popupX + 350, popupY + 340, 100, 40},
                      "ESC")) {
          isPopupOpen = false; // Chiudi il popup
        }

        if (courseExists(userInput) || !isValidCourseName(userInput)) {
          if (courseExists(userInput))
            DrawText("Course already exists", popupX + 30, popupY + 200, 20,
                     RED);

          if (!isValidCourseName(userInput))
            DrawText("Invalid name. (3-50 char)", popupX + 30, popupY + 200, 20,
                     RED);

          canSave = false;
        } else
          canSave = true;

        // Pulsante "Salva" nel popup
        if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40},
                      "Salva")) {
          if (canSave) {
            writeNewCourse(userInput);
          }
        }
      }
    } else if (currentState == APP_STATE_CLASSES) {
      // Schermata principale
      // Barra laterale sinistra
      sidebar(currentState, quit);

      // Area principale destra
      mainArea("Classes");

      // Disegna il pulsante "+"
      addNewButton();

      // Righe della tabella
      int i = 0;
      ifstream classesFile(classesDataPath);
      string line;
      while (getline(classesFile, line)) {
        vector<string> splitLine = splitString(line, ',');
        i++;
        DrawRectangle((float)(screenWidth / 3 + 75), 90 + i * 60,
                      (float)(screenWidth / 2 + 100), 50, DARKGRAY);
        DrawText("Class Name", (float)(screenWidth / 3 + 100),
                 (float)(100 + i * 60), 20, WHITE);
        DrawText(splitLine[2].c_str(), (float)(screenWidth / 3 + 250),
                 (float)(100 + i * 60), 20, WHITE);
        DrawText("ID", (float)(screenWidth / 3 + 500), (float)(100 + i * 60),
                 20, WHITE);
        DrawText(splitLine[0].c_str(), (float)(screenWidth / 3 + 550),
                 (float)(100 + i * 60), 20, WHITE);
        DrawText("ID CO", (float)(screenWidth / 3 + 615), (float)(100 + i * 60),
                 20, WHITE);
        DrawText(splitLine[1].c_str(), (float)(screenWidth / 3 + 700),
                 (float)(100 + i * 60), 20, WHITE);

        // Icone di modifica e eliminazione
        DrawTextureEx(note,
                      (Vector2){(float)(float)(screenWidth / 3 + 800),
                                (float)(100 + i * 60)},
                      0, 1, WHITE);
        DrawTextureEx(percent,
                      (Vector2){(float)(float)(screenWidth / 3 + 850),
                                (float)(100 + i * 60)},
                      0, 1, WHITE);
        DrawTextureEx(del,
                      (Vector2){(float)(float)(screenWidth / 3 + 900),
                                (float)(100 + i * 60)},
                      0, 1, WHITE);
        DrawTextureEx(more,
                      (Vector2){(float)(float)(screenWidth / 3 + 950),
                                (float)(100 + i * 60)},
                      0, 1, WHITE);
      }
    } else if (currentState == APP_STATE_STUDENT) {
      // Schermata principale
      // Barra laterale sinistra
      sidebar(currentState, quit);

      // Area principale destra
      mainArea("Students");

      // Pulsante +
      addNewButton();

      // Righe della tabella
      int i = 0;
      ifstream studentsFile(studentsDataPath);
      string line;
      while (getline(studentsFile, line)) {
        vector<string> splitLine = splitString(line, ',');
        i++;
        DrawRectangle((float)(screenWidth / 3 + 75), 90 + i * 60,
                      (float)(screenWidth / 2 + 100), 50, DARKGRAY);
        DrawText("Student Name", (float)(screenWidth / 3 + 100),
                 (float)(100 + i * 60), 20, WHITE);
        DrawText(splitLine[3].c_str(), (float)(screenWidth / 3 + 275),
                 (float)(100 + i * 60), 20, WHITE);
        DrawText("ID", (float)(screenWidth / 3 + 600), (float)(100 + i * 60),
                 20, WHITE);
        DrawText(splitLine[0].c_str(), (float)(screenWidth / 3 + 650),
                 (float)(100 + i * 60), 20, WHITE);

        // Icone di modifica e eliminazione
        DrawTextureEx(note,
                      (Vector2){(float)(float)(screenWidth / 3 + 800),
                                (float)(100 + i * 60)},
                      0, 1, WHITE);
        DrawTextureEx(percent,
                      (Vector2){(float)(float)(screenWidth / 3 + 850),
                                (float)(100 + i * 60)},
                      0, 1, WHITE);
        DrawTextureEx(del,
                      (Vector2){(float)(float)(screenWidth / 3 + 900),
                                (float)(100 + i * 60)},
                      0, 1, WHITE);
        DrawTextureEx(more,
                      (Vector2){(float)(float)(screenWidth / 3 + 950),
                                (float)(100 + i * 60)},
                      0, 1, WHITE);
      }

      // Disegna il pulsante "+"
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
