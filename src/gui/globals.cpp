#include "../../include/gui/globals.h"

// Textures
Texture2D logoImage;
Texture2D check;
Texture2D del;
Texture2D note;
Texture2D more;
Texture2D percent;
Texture2D add;

// Font
Font customfont;

void loadResources() {
  logoImage = LoadTexture("../assets/Logo-edu.png");
  check = LoadTexture("../assets/check.png");
  del = LoadTexture("../assets/delete.png");
  note = LoadTexture("../assets/note.png");
  more = LoadTexture("../assets/more.png");
  percent = LoadTexture("../assets/percent.png");
  add = LoadTexture("../assets/add.png");

  customfont = LoadFontEx("../assets/Poppins-Regular.ttf", 20, 0, 0);
}
