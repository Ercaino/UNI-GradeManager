#include "../../include/cli/utils.h"
#include <fstream>
#include <iostream>
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
