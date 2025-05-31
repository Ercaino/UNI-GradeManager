#ifndef GLOBALS_H
#define GLOBALS_H

#include <cmath>
#include <raylib.h>

enum AppState {
  APP_STATE_LOGIN,
  APP_STATE_COURSES,
  APP_STATE_CLASSES,
  APP_STATE_STUDENT
};

// Impostazione delle dimensioni della finestra
const float screenWidth = 1600;
const float screenHeight = 900;

const float mainAreaWidth = screenWidth / 4 * 3;
const float sidebarWidth = screenWidth / 4;

const float popupWidth = 600;
const float popupHeight = 400;
const float popupX = screenWidth / 2 - popupWidth / 2;
const float popupY = screenHeight / 2 - popupHeight / 2;

const float tableOuterPadding = sidebarWidth + mainAreaWidth * 0.05;
const float tableWidth = mainAreaWidth * 0.9;
const float tableInnerPadding = mainAreaWidth * 0.03;

const int regularFontSize = round(screenWidth * screenHeight * 0.000016599);
const int boldFontSize = round(screenWidth * screenHeight * 0.00002436);
const int blackFontSize = round(screenWidth * screenHeight * 0.00003478);

extern Texture2D logoImage;
extern Texture2D check;
extern Texture2D del;
extern Texture2D note;
extern Texture2D more;
extern Texture2D percent;
extern Texture2D add;
extern Texture2D dropdownArrow;
extern Texture2D dropdownArrowRight;

extern Font poppinsRegular;
extern Font poppinsBlack;
extern Font poppinsBold;

void loadResources();

#endif
