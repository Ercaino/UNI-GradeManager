#ifndef GLOBALS_H
#define GLOBALS_H

#include <raylib.h>

enum AppState {
  APP_STATE_LOGIN,
  APP_STATE_COURSES,
  APP_STATE_CLASSES,
  APP_STATE_STUDENT
};

// Impostazione delle dimensioni della finestra
const int screenWidth = 1600;
const int screenHeight = 900;

extern Texture2D logoImage;
extern Texture2D check;
extern Texture2D del;
extern Texture2D note;
extern Texture2D more;
extern Texture2D percent;
extern Texture2D add;

extern Font customfont;

void loadResources();

#endif
