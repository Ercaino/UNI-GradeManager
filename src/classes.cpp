#include "../include/classes.h"
#include "../include/courses.h"
#include "../include/students.h"
#include "../include/utils.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool classExists(const int &courseId, const string &className) {
  ifstream classesFile(classesDataPath);
  // Come prima, se non esiste il file non ci possono essere classi quindi
  // ritorno false
  if (!classesFile.is_open()) {
    return false;
  }

  string line;
  while (getline(classesFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    // splitLine[0] è l'ID della classe, splitLine[1] è l'ID del corso e
    // splitLine[2] è il nome della classe
    if (splitLine[1] == to_string(courseId) && splitLine[2] == className) {
      return true;
    }
  }

  return false;
}

bool isValidClassName(const string &className) {
  // Un nome di classe è valido se è una singola lettera compresa tra A e Z
  return className.length() == 1 && className >= "A" && className <= "Z";
}

string inputClassName() {
  cout << "Insert a letter for the class (A-Z): ";

  string className;
  cin >> className;
  cin.ignore();

  while (!isValidClassName(className)) {
    cout << "Please enter a valid letter (A-Z):" << endl;
    cin >> className;
  }

  return className;
}

int writeNewClass(const int &course, const string &className) {
  ofstream classesFile(classesDataPath, ios::app);
  if (!classesFile.is_open()) {
    return -1;
  }

  int lastId = getLastId(classesDataPath);
  classesFile << to_string(lastId + 1) + "," + to_string(course) + "," +
                     className
              << endl;
  return 0;
}

void addNewClass() {
  const int courseId = chooseCourse();

  string className = inputClassName();

  while (classExists(courseId, className)) {
    cout << "Class " + className + " already exists in this course." << endl;
    className = inputClassName();
  }

  ofstream classesFile(classesDataPath, ios::app);
  int lastId = getLastId(classesDataPath);
  classesFile << to_string(lastId + 1) + "," + to_string(courseId) + "," +
                     className
              << endl;

  cout << "Class " + className + " added successfully." << endl;
}

void listClasses() {
  ifstream coursesFile(coursesDataPath);
  string courseLine;

  cout << endl << "============ Classes ============" << endl;
  // Legge ogni corso
  while (getline(coursesFile, courseLine)) {
    vector<string> splitCourseLine = splitString(courseLine, ',');
    cout << "- " + splitCourseLine[1] << endl;

    ifstream readClassFile(
        classesDataPath); // Il file va ridichiarato ad ogni iterazione o il
                          // flusso del file non funziona correttamente
    string classLine;
    // Per ogni corso, legge ogni classe
    while (getline(readClassFile, classLine)) {
      vector<string> splitClassLine = splitString(classLine, ',');
      // Se l'ID del corso della classe corrisponde all'ID del corso allora la
      // stampo
      if (splitClassLine[1] == splitCourseLine[0]) {
        cout << "  |- " << splitClassLine[0] + ". Class " + splitClassLine[2]
             << endl;
      }
    }
  }
}

// Funzione per ottenere l'ID del corso da un ID di classe
int getCourseIdFromClassId(const int &classId) {
  ifstream classesFile(classesDataPath);
  string line;

  while (getline(classesFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    if (stoi(splitLine[0]) == classId) {
      return stoi(splitLine[1]);
    }
  }

  return -1;
}

bool classHasStudents(const int &classId) {
  ifstream studentsFile(studentsDataPath);
  string line;

  // Itera su ogni riga del file degli studenti, se ce n'e' almeno uno che ha
  // l'id della classe ritorna true
  while (getline(studentsFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    if (stoi(splitLine[1]) == classId) {
      return true;
    }
  }

  return false;
}

int chooseClass(const int &mode) {
  int choice;
  listClasses();
  switch (mode) {
  case 1:
    cout << "Choose the class to which you want to add a student: ";
    break;
  case 2:
    cout << "Choose the class to which you want to add grades: ";
    break;
  case 3:
    cout << "Choose the class for which you want to view grades and students: ";
    break;
  case 4:
    cout << "Choose the class for which you want to calculate the average "
            "grade: ";
    break;
  }
  cin >> choice;

  while (choice < 1 || choice > getLastId(classesDataPath)) {
    cout << "Please enter a valid class Id: ";
    cin >> choice;
  }

  return choice;
}
