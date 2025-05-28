#include "../include/classes.h"
#include "../include/courses.h"
#include "../include/grades.h"
#include "../include/students.h"

#include <iostream>

using namespace std;

void printMainMenu() {
  cout << endl;
  cout << "============ Main menu ============" << endl;
  cout << "1. Add new course" << endl;
  cout << "2. Add new class to a course" << endl;
  cout << "3. Add student to a class" << endl;
  cout << "4. Add grades" << endl;
  cout << "5. Display information" << endl;
  cout << "0. Exit" << endl;
}

void printGradesMenu() {
  cout << endl;
  cout << "============ Grades menu ============" << endl;
  cout << "1. Add grades for all the students in a class" << endl;
  cout << "2. Add grades for a single student" << endl;
}

void printInformationMenu() {
  cout << endl;
  cout << "============ Information menu ============" << endl;
  cout << "1. List students and their grades in a class" << endl;
  cout << "2. Show average grade for a student" << endl;
  cout << "3. Show average grade for a class" << endl;
  cout << "4. Show average grade for a course" << endl;
}

int main(int argc, char *argv[]) {
  int choice;
  printMainMenu();
  cout << "Your choice: ";
  cin >> choice;
  cin.ignore();

  while (choice != 0) {
    switch (choice) {
    case 1:
      addNewCourse();
      break;
    case 2:
      addNewClass();
      break;
    case 3:
      addNewStudent();
      break;
    case 4:
      printGradesMenu();
      cout << "Your choice: ";
      cin >> choice;
      switch (choice) {
      case 1:
        addGradesToClass();
        break;
      case 2:
        addGradesToStudent();
        break;
      default:
        cout << "Please enter a valid number." << endl;
      }
      break;
    case 5:
      printInformationMenu();
      cout << "Your choice: ";
      cin >> choice;
      switch (choice) {
      case 1:
        listStudentsAndGradesInAClass();
        break;
      case 2:
        showAverageForStudent();
        break;
      case 3:
        showAverageForClass();
        break;
      case 4:
        showAverageForCourse();
        break;
      default:
        cout << "Please enter a valid number." << endl;
      }
      break;
    default:
      cout << "Please enter a valid number." << endl;
    }
    printMainMenu();
    cout << "Your choice: ";
    cin >> choice;
  }

  return 0;
}
