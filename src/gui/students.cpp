#include "../../include/gui/students.h"
#include "../../include/gui/classes.h"
#include "../../include/gui/courses.h"
#include "../../include/gui/grades.h"
#include "../../include/gui/utils.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// N.B.!!! Non confondere lo studentId con lo studentNumber, il primo e' l'id
// universitario (S7706624), il secondo e' il numero "globale" dello studente
// (1, 2, 3, ...), un id a parte che serve per il programma

bool studentExists(const int classId, const string studentId) {
  ifstream readStudentsFile(studentsDataPath);
  // Di nuovo, se il file non esiste non esistono studenti, quindi ritorno false
  if (!readStudentsFile.is_open()) {
    return false;
  }

  string line;
  // Leggo il file riga per riga e controllo se esiste uno studente con lo
  // stesso id, e id classe (ogni studente puo' appartenere a piu' classi)
  while (getline(readStudentsFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    if (splitLine[1] == studentId && splitLine[2] == to_string(classId)) {
      return true;
    }
  }
  return false;
}

bool isValidStudentId(const string &studentId) {
  // Il formato dello studentId deve essere S7706624, quindi:
  // - Deve iniziare con 'S' o 's'
  // - Deve essere lungo 8 caratteri
  // - I restanti 7 caratteri devono essere numeri
  if (studentId.length() != 8 || (studentId[0] != 's' && studentId[0] != 'S')) {
    return false;
  }

  for (size_t i = 1; i < studentId.length(); ++i) {
    if (!isdigit(studentId[i])) {
      return false;
    }
  }

  return true;
}

string inputStudentId() {
  cout << "Insert the student ID: ";

  string studentId;
  cin >> studentId;
  cin.ignore();

  while (!isValidStudentId(studentId)) {
    cout << "Please enter a valid ID:" << endl;
    cin >> studentId;
  }

  return studentId;
}

bool isValidStudentName(const string &studentName) {
  // Il nome dello studente non puo' essere vuoto e non puo' superare i 20
  if (studentName.empty() || studentName.length() > 20) {
    return false;
  }

  // Controllo che il nome contenga solo lettere e spazi
  for (char c : studentName) {
    if (!isalpha(c) && c != ' ') {
      return false;
    }
  }

  return true;
}

string inputStudentName() {
  cout << "Insert the student name (max. 20 characters): ";

  string studentName;
  cin >> studentName;
  cin.ignore();

  while (!isValidStudentName(studentName)) {
    cout << "Please enter a valid name:" << endl;
    cin >> studentName;
  }

  return studentName;
}

int writeNewStudent(const int &classId, const string &studentId,
                    const string &studentName) {
  ofstream studentsFile(studentsDataPath, ios::app);
  if (!studentsFile.is_open()) {
    return -1; // Error opening file
  }

  // Ottiene l'ultimo ID dello studente e lo incrementa di 1 per il nuovo
  // studente
  int lastId = getLastId(studentsDataPath);
  studentsFile << to_string(lastId + 1) + "," + to_string(classId) + "," +
                      studentId + "," + studentName
               << endl;
  return 0;
}

void addNewStudent() {
  const int classId = chooseClass();

  string studentId = inputStudentId();

  while (studentExists(classId, studentId)) {
    cout << "Student " + studentId + " already exists in this class." << endl;
    studentId = inputStudentId();
  }

  string studentName = inputStudentName();

  if (writeNewStudent(classId, studentId, studentName) == -1) {
    cout << "Error writing to file. Please try again." << endl;
    return;
  }

  cout << "Student added successfully." << endl;
}

void listStudents() {
  ifstream coursesFile(coursesDataPath);
  string courseLine;

  cout << endl << "============ Students ============" << endl;
  // Itera attraverso ogni riga del file dei corsi
  while (getline(coursesFile, courseLine)) {
    vector<string> splitCourseLine = splitString(courseLine, ',');
    cout << "- " + splitCourseLine[1] << endl;

    ifstream classesFile(classesDataPath);
    string classLine;

    // Itera attraverso ogni riga del file delle classi
    while (getline(classesFile, classLine)) {
      vector<string> splitClassLine = splitString(classLine, ',');

      // Se la classe appartiene al corso corrente, stampa le informazioni
      if (splitClassLine[1] == splitCourseLine[0]) {
        cout << "  |- Class " + splitClassLine[2] << endl;

        ifstream studentsFile(studentsDataPath);
        string studentLine;

        // Itera attraverso ogni riga del file degli studenti
        while (getline(studentsFile, studentLine)) {
          vector<string> splitStudentLine = splitString(studentLine, ',');

          // Se lo studente appartiene alla classe corrente, lo stampo
          if (splitStudentLine[1] == splitClassLine[0]) {
            cout << "    |- "
                 << splitStudentLine[0] +
                        " Student: ID = " + splitStudentLine[2] +
                        ", Name = " + splitStudentLine[3]
                 << endl;
          }
        }
      }
    }
  }
}

int getClassIdFromStudentNumber(const int &studentNumber) {
  ifstream readStudentsFile(studentsDataPath);
  if (!readStudentsFile.is_open()) {
    return -1;
  }

  string line;
  while (getline(readStudentsFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    if (splitLine[0] == to_string(studentNumber)) {
      return stoi(splitLine[1]);
    }
  }
  return -1;
}

string getStudentIdFromStudentNumber(const int &studentNumber) {
  ifstream readStudentsFile(studentsDataPath);
  if (!readStudentsFile.is_open()) {
    return "";
  }

  string line;
  while (getline(readStudentsFile, line)) {
    vector<string> splitLine = splitString(line, ',');
    if (splitLine[0] == to_string(studentNumber)) {
      return splitLine[2];
    }
  }
  return "";
}

bool studentHasGrades(const int &studentNumber) {
  ifstream readGradesFile(gradesDataPath);
  string gradeLine;

  while (getline(readGradesFile, gradeLine)) {
    vector<string> splitGradeLine = splitString(gradeLine, ',');

    if (stoi(splitGradeLine[2]) == studentNumber) {
      return true;
    }
  }

  return false;
}
