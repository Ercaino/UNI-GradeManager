#include "../../include/gui/utils.h"
#include "../../include/gui/colors.h"
#include "../../include/gui/globals.h"
#include <fstream>
#include <iostream>
#include <raylib.h>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<string> splitString(const string &str, const char &delimiter) {
  vector<string> result;
  stringstream ss(str);
  string token;

  while (getline(ss, token, delimiter)) {
    result.push_back(token);
  }

  return result;
}

int getLastId(const string &filePath) {
  ifstream file(filePath);
  if (!file.is_open()) {
    return 0;
  }
  string line;
  int id = 0;
  while (getline(file, line)) {
    ++id;
  }
  return id;
}

void deleteLine(const string &filePath, int lineNumber) {
  ifstream inputFile(filePath);
  if (!inputFile.is_open()) {
    cerr << "Error: Could not open file for reading.\n";
    return;
  }

  vector<string> lines;
  string line;
  while (getline(inputFile, line)) {
    lines.push_back(line);
  }
  inputFile.close();

  if (lineNumber < 1 || lineNumber > static_cast<int>(lines.size())) {
    cerr << "Error: Invalid line number.\n";
    return;
  }

  lines.erase(lines.begin() + (lineNumber - 1));

  ofstream outputFile(filePath);
  if (!outputFile.is_open()) {
    cerr << "Error: Could not open file for writing.\n";
    return;
  }

  for (const auto &l : lines) {
    outputFile << l << '\n';
  }
  outputFile.close();

  cout << "Line " << lineNumber << " has been deleted successfully.\n";
}

void DrawRegularText(const string &text, Vector2 position, float fontSize,
                     unsigned int color) {
  DrawTextEx(poppinsRegular, text.c_str(), position, fontSize, 1,
             GetColor(color));
};

void DrawBoldText(const string &text, Vector2 position, float fontSize,
                  unsigned int color) {
  DrawTextEx(poppinsBold, text.c_str(), position, fontSize, 1, GetColor(color));
};

void DrawBlackText(const string &text, Vector2 position, float fontSize,
                   unsigned int color) {
  DrawTextEx(poppinsBlack, text.c_str(), position, fontSize, 1,
             GetColor(color));
};

float regularTextPadding(const string &text) {
  return MeasureTextEx(poppinsRegular, text.c_str(), regularFontSize, 1).x;
}
float boldTextPadding(const string &text) {
  return MeasureTextEx(poppinsBold, text.c_str(), boldFontSize, 1).x;
}
float blackTextPadding(const string &text) {
  return MeasureTextEx(poppinsBlack, text.c_str(), blackFontSize, 1).x;
}
