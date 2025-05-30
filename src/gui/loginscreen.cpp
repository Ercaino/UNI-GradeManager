#include "../../include/gui/loginscreen.h"
#include "../../include/gui/colors.h"
#include "../../include/gui/globals.h"
#include "../../include/gui/raygui.h"

void loginScreen(AppState &currentState, bool &quit) {
  DrawTextEx(
      customfont, "UNI - Manage System",
      (Vector2){static_cast<float>(screenWidth / 2 -
                                   MeasureText("UNI - Manage System", 30) / 2),
                static_cast<float>(screenHeight / 4 + 150)},
      40, 1, GetColor(textColor));

  DrawTextureEx(logoImage,
                (Vector2){screenWidth / 2 - 100, screenHeight / 4 - 100}, 0,
                0.4, WHITE);

  // Pulsanti Login e Quit
  if (GuiButton((Rectangle){(float)(screenWidth / 2 - 100),
                            (float)(screenHeight / 2), 200, 75},
                "Login")) {
    currentState = APP_STATE_COURSES; // Passa alla schermata principale
  }

  if (GuiButton((Rectangle){(float)(screenWidth / 2 - 100),
                            (float)(screenHeight / 2 + 100), 200, 75},
                "Quit")) {
    quit = true;
  }
}
