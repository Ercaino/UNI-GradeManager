#include "../../include/gui/colors.h"
#include "../../include/gui/globals.h"
#include "../../include/gui/raygui.h"
#include <raylib.h>

void sidebarButtons(AppState &currentState, bool &quit) {
  if (GuiButton((Rectangle){(float)(screenWidth / 16 + 10),
                            float(screenHeight / 4 + 50), 300, 75},
                "Courses")) {
    currentState = APP_STATE_COURSES;
  }
  if (GuiButton((Rectangle){(float)(screenWidth / 16 + 10),
                            float(screenHeight / 4 + 150), 300, 75},
                "Classes")) {
    currentState = APP_STATE_CLASSES;
  }
  if (GuiButton((Rectangle){(float)(screenWidth / 16 + 10),
                            float(screenHeight / 4 + 250), 300, 75},
                "Students")) {
    currentState = APP_STATE_STUDENT;
  }
  if (GuiButton((Rectangle){(float)(screenWidth / 16 + 10),
                            float(screenHeight / 4 + 500), 300, 75},
                "Quit")) {
    quit = true;
  }
  return;
}

void sidebarContainer() {
  DrawRectangle(0, 0, (float)(screenWidth / 3), screenHeight,
                GetColor(sidebarBackgroundColor));
}

void sidebarLogo() {
  // Logo nella barra laterale
  DrawTextEx(customfont, "UNI - Manage System",
             (Vector2){static_cast<float>(
                           245 - MeasureText("UNI - Manage System", 20) / 2),
                       175},
             30, 1, GetColor(textColor));
  DrawTextureEx(
      logoImage,
      (Vector2){(float)(screenWidth / 8 + 10), float(screenHeight / 16)}, 0,
      0.2, WHITE);
}

void sidebar(AppState &currentState, bool &quit) {
  sidebarContainer();
  sidebarLogo();
  sidebarButtons(currentState, quit);
}
