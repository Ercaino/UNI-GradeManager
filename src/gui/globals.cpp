#include "../../include/gui/globals.h"
#include <raylib.h>

// Textures
Texture2D logoImage;
Texture2D check;
Texture2D del;
Texture2D note;
Texture2D more;
Texture2D percent;
Texture2D add;
Texture2D dropdownArrow;
Texture2D dropdownArrowRight;

// Fonts
Font poppinsRegular;
Font poppinsBlack;
Font poppinsBold;

void loadResources() {
  logoImage = LoadTexture("../assets/Logo-edu.png");
  check = LoadTexture("../assets/check.png");
  del = LoadTexture("../assets/delete.png");
  note = LoadTexture("../assets/note.png");
  more = LoadTexture("../assets/more.png");
  percent = LoadTexture("../assets/percent.png");
  add = LoadTexture("../assets/add.png");
  dropdownArrow = LoadTexture("../assets/dropdown-arrow.png");
  dropdownArrowRight = LoadTexture("../assets/dropdown-arrow-right.png");

  poppinsRegular = LoadFontEx("../assets/Poppins-Regular.ttf", 24, 0, 0);
  poppinsBlack = LoadFontEx("../assets/Poppins-Black.ttf", 50, 0, 0);
  poppinsBold = LoadFontEx("../assets/Poppins-Bold.ttf", 35, 0, 0);
}
