#include "../../include/gui/colors.h"
#include "../../include/gui/globals.h"
#include "../../include/gui/raygui.h"
#include "utils.h"
#include <raylib.h>
using namespace std;

void sidebarButtons(AppState &currentState, bool &quit) {
  if (GuiButton((Rectangle){sidebarWidth * 15 / 100, screenHeight / 4 + 50,
                            sidebarWidth * 70 / 100, 75},
                "Courses")) {
    currentState = APP_STATE_COURSES;
  }
  if (GuiButton((Rectangle){sidebarWidth * 15 / 100, screenHeight / 4 + 150,
                            sidebarWidth * 70 / 100, 75},
                "Classes")) {
    currentState = APP_STATE_CLASSES;
  }
  if (GuiButton((Rectangle){sidebarWidth * 15 / 100, screenHeight / 4 + 250,
                            sidebarWidth * 70 / 100, 75},
                "Students")) {
    currentState = APP_STATE_STUDENT;
  }
  if (GuiButton((Rectangle){sidebarWidth * 15 / 100, screenHeight / 4 + 500,
                            sidebarWidth * 70 / 100, 75},
                "Quit")) {
    quit = true;
  }
  return;
}

void sidebarContainer() {
  DrawRectangle(0, 0, float(screenWidth / 4), screenHeight,
                GetColor(sidebarBackgroundColor));
}

void sidebarLogo() {
  // Logo nella barra laterale
  float scale = screenWidth * screenHeight * 0.0000002;

  DrawBoldText(
      "UNI - Manage System",
      {float((sidebarWidth / 2) -
             float(MeasureTextEx(poppinsBold, "UNI - Manage System", 35, 1).x /
                   2)),
       screenHeight / 4});
  DrawTextureEx(logoImage,
                {sidebarWidth / 2 - (500 * scale / 2), screenHeight / 16}, 0,
                scale, WHITE);
}

void sidebar(AppState &currentState, bool &quit) {
  sidebarContainer();
  sidebarLogo();
  sidebarButtons(currentState, quit);
}
