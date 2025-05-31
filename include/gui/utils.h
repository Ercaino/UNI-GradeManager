#ifndef UTILS_H
#define UTILS_H
#include "colors.h"
#include "globals.h"
#include <raylib.h>
#include <string>
#include <vector>

using namespace std;

vector<string> splitString(const string &, const char &);
int getLastId(const string &);
void DrawRegularText(const string &text, Vector2 position,
                     float fontSize = regularFontSize,
                     unsigned int color = textColor);
void DrawBoldText(const string &text, Vector2 position,
                  float fontSize = boldFontSize,
                  unsigned int color = textColor);
void DrawBlackText(const string &text, Vector2 position,
                   float fontSize = blackFontSize,
                   unsigned int color = textColor);
float regularTextPadding(const string &text);
float boldTextPadding(const string &text);
float blackTextPadding(const string &text);
void deleteLine(const string &, int);

#endif
