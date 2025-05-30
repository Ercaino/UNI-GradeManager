#include "../../include/gui/courses.h"
#include "../../include/gui/classes.h"
#include "../../include/gui/utils.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool courseExists(const string &courseName) {
  ifstream courseFile(coursesDataPath);
  // Se il file non esiste ritorna false visto che non ci sono corsi
  if (!courseFile.is_open()) {
    return false;
  }

  string line;
  // Legge ogni riga del file, la separa in un vettore di stringhe ad ogni "," e
  // verifica se il nome del corso esiste
  while (getline(courseFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    // splitLine[0] è l'ID del corso, splitLine[1] è il nome del corso
    if (splitLine[1] == courseName) {
      return true;
    }
  }

  return false;
}

bool isValidCourseName(const string &courseName) {
  // Un nome di corso è valido se non è vuoto, ha una lunghezza compresa tra 3
  // e 50 caratteri e non contiene virgole (almeno non si rompe tutto)
  return !courseName.empty() && courseName.length() <= 50 &&
         courseName.length() >= 3 && courseName.find(',') == string::npos;
}

string inputCourseName() {

  string courseName;
  getline(cin, courseName);

  while (!isValidCourseName(courseName)) {
    cout << "Please enter a valid name (max. 50 char. and don't use commas): ";
    getline(cin, courseName);
  }

  return courseName;
}

int writeNewCourse(const string &courseName) {
  ofstream courseFile(coursesDataPath, ios::app);
  if (!courseFile.is_open()) {
    return -1; // Error opening file
  }

  // Ottiene l'ultimo ID del corso e lo incrementa di 1 per il nuovo corso
  int lastId = getLastId(coursesDataPath);
  courseFile << to_string(lastId + 1) + "," + courseName << endl;
  return 0;
}

void addNewCourse() {
  string line;
  string courseName;

  courseName = inputCourseName();

  while (courseExists(courseName)) {
    cout << "Course " + courseName +
                " already exists. Please enter a new name: ";
    courseName = inputCourseName();
  }

  if (writeNewCourse(courseName) == -1) {
    cout << "Error writing to file. Please try again." << endl;
    return;
  }

  cout << "Course added successfully." << endl;
}

void listCourses() {
  ifstream coursesFile(coursesDataPath);
  string line;

  cout << endl << "============ Courses ============" << endl;
  // Loop attraverso ogni riga del file dei corsi
  while (getline(coursesFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    cout << splitLine[0] + ". " + splitLine[1] << endl;
  }
}

// Funzione per ottenere il nome del corso dato l'ID
string getCourseNameFromId(const int &courseId) {
  ifstream coursesFile(coursesDataPath);
  string line;

  while (getline(coursesFile, line)) {
    // Legge ogni riga e returna il nome del corso se l'ID corrisponde
    vector<string> splitLine = splitString(line, ',');
    if (splitLine[0] == to_string(courseId)) {
      return splitLine[1];
    }
  }
  return "";
}

bool courseHasClasses(const int &courseId) {
  ifstream classesFile(classesDataPath);
  string line;

  while (getline(classesFile, line)) {
    vector<string> splitLine = splitString(line, ',');

    // Se esiste anche solo una classe con l'ID del corso, ritorna true
    if (stoi(splitLine[1]) == courseId) {
      return true;
    }
  }

  return false;
}

int chooseCourse() {
  listCourses();
  cout << "Choose the course to which you want to add a class: ";

  int choice;
  cin >> choice;

  // Se l'utente inserisce un numero piu' alto dell'ultimo ID del corso o minore
  // di 1, richiedo l'input
  while (choice < 1 || choice > getLastId(coursesDataPath)) {
    cout << "Please enter a valid course number: ";
    cin >> choice;
  }

  return choice;
}
