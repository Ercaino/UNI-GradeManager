#include "../../include/gui/popup.h"
#include "../../include/gui/colors.h"
#include "../../include/gui/globals.h"
#include "../../include/gui/raygui.h"

#include "../../include/gui/courses.h"
#include "../../include/gui/classes.h"
#include "../../include/gui/students.h"
#include "../../include/gui/utils.h"

#include <raylib.h>
#include <cstring>
#include <iostream>

// Dimensioni e posizione del popup
int popupWidth = 600;
int popupHeight = 400;
int popupX = screenWidth / 2 - popupWidth / 2;
int popupY = screenHeight / 2 - popupHeight / 2;

// Variable save/delete button
bool canSave = true;
bool canDelete = true;

// Variable dropmenu
int activeOption = 0;        // Index of the currently selected option
bool dropdownActive = false; // Is the dropdown expanded?
bool focusOnId = false;

// Variable input
char userInputAddCourses[256] = "";

char userInputAddClassesName[256] = "";
int userInputAddCourseId = 0;

char userInputAddStudentsName[256] = "";
char userInputAddStudentsId[256] = "";
char userInputAddClassesId[256] = "";

char userInputDeleteCourses[256] = "";
char userInputDeleteClasses[256] = "";
char userInputDeleteStudents[256] = "";

char userInputAddVoteClasses[256] = "";
char userInputAddVoteStudents[256] = "";

// Controll Mouse
void controllMouse(int &popupX, int &popupY)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionPointRec(
                GetMousePosition(),
                {(float)popupX + 200, (float)popupY + 130, 300, 40}))
        {
            focusOnId = false; // Focus on "Name" text box
        }
        else if (CheckCollisionPointRec(
                     GetMousePosition(),
                     {(float)popupX + 200, (float)popupY + 210, 300, 40}))
        {
            focusOnId = true; // Focus on "ID" text box
        }
    }
}

// BeginPopUP
void popup(const char *title)
{
    // Dim schermo
    DrawRectangle(0, 0, screenWidth, screenHeight, GetColor(coverColor));

    // Disegna il rettangolo del popup
    DrawRectangle(popupX, popupY, popupWidth, popupHeight,
                  GetColor(popUpBack));
    DrawRectangleLines(popupX, popupY, popupWidth, popupHeight, BLACK);

    // Disegna barra
    DrawRectangle(popupX, popupY, popupWidth, popupHeight / 4 - 10,
                  GetColor(popUpBar));
    DrawText(title, popupX + 30, popupY + 35, 20,
             GetColor(textColor));
}

// Button for esc popup
void buttonEsc(bool &isPopupOpen)
{
    // Pulsante "Chiudi" nel popup
    if (GuiButton((Rectangle){popupX + 350, popupY + 340, 100, 40},
                  "ESC"))
    {
        isPopupOpen = false; // Chiudi il popup
    }
}

// For stoi
bool isValidNumber(const char charArray[])
{
    for (int i = 0; charArray[i] != '\0'; ++i)
    {
        if (!std::isdigit(charArray[i]))
        {
            return false; // Restituisce false se trova un carattere non numerico
        }
    }
    return charArray[0] != '\0'; // Restituisce true solo se la stringa non è vuota
}
// da Char a Int
int charInt(const char charArray[])
{
    if (!isValidNumber(charArray))
    {
        std::cerr << "Errore: Input non valido per la conversione." << std::endl;
        return -1; // Restituisce un valore di errore (ad esempio, -1)
    }

    std::string str(charArray); // Converte char[] in std::string
    try
    {
        int StudentId = std::stoi(str);
        return StudentId;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Errore: Input non valido per la conversione." << std::endl;
        return -1; // Restituisce un valore di errore
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Errore: Il numero è fuori dal range rappresentabile." << std::endl;
        return -1; // Restituisce un valore di errore
    }
}

// Button add
void popupAddCourses(bool &isPopupOpen, bool &quit)
{
    // Disegna il popup se è aperto
    if (isPopupOpen)
    {
        const char *title = "Add Courses";
        popup(title);

        // Testo nel popup
        DrawText("Course Name", popupX + 30, popupY + 140, 20,
                 GetColor(textColor));
        GuiTextBox({(float)popupX + 200, (float)popupY + 130, 300, 40},
                   userInputAddCourses, 255, true);

        // Pulsante "Chiudi" nel popup
        buttonEsc(isPopupOpen);

        if (courseExists(userInputAddCourses) || !isValidCourseName(userInputAddCourses))
        {
            if (courseExists(userInputAddCourses))
                DrawText("Course already exists", popupX + 30, popupY + 200, 20,
                         RED);

            if (!isValidCourseName(userInputAddCourses))
                DrawText("Invalid name. (3-50 char)", popupX + 30, popupY + 200, 20,
                         RED);

            canSave = false;
        }
        else
            canSave = true;

        // Pulsante "Salva" nel popup
        if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40},
                      "Save"))
        {
            if (canSave)
            {
                writeNewCourse(userInputAddCourses);
                strcpy(userInputAddCourses, "");
                isPopupOpen = false; // Chiudi il popup
            }
        }
    }
}
void popupAddClasses(bool &isPopupOpen, bool &quit)
{
    // Disegna il popup se è aperto
    if (isPopupOpen)
    {
        const char *title = "Add Classes";
        popup(title);

        // Testo nel popup
        // Name
        DrawText("Classes Name", popupX + 30, popupY + 140, 20,
                 GetColor(textColor));
        GuiTextBox({(float)popupX + 200, (float)popupY + 130, 300, 40},
                   userInputAddClassesName, 255, !focusOnId);
        // DropDown Course
        DrawText("In Course", popupX + 30, popupY + 200, 20,
                 GetColor(textColor));

        // Controll mouse
        controllMouse(popupX, popupY);

        // Pulsante "Chiudi" nel popup
        buttonEsc(isPopupOpen);

        if (classExists(userInputAddCourseId, userInputAddClassesName) || !isValidClassName(userInputAddClassesName))
        {
            if (classExists(userInputAddCourseId, userInputAddClassesName))
                DrawText("Course already exists", popupX + 30, popupY + 275, 20,
                         RED);

            if (!isValidClassName(userInputAddClassesName))
                DrawText("Invalid name. (3-50 char)", popupX + 30, popupY + 275, 20,
                         RED);

            canSave = false;
        }
        else
            canSave = true;

        // Pulsante "Salva" nel popup
        if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40},
                      "Save"))
        {
            if (canSave)
            {
                writeNewClass(userInputAddCourseId, userInputAddClassesName);
                strcpy(userInputAddClassesName, "");
                userInputAddCourseId = 0;
                isPopupOpen = false; // Chiudi il popup
            }
        }
    }
}
void popupAddStudents(bool &isPopupOpen, bool &quit)
{
    // Disegna il popup se è aperto
    if (isPopupOpen)
    {
        const char *title = "Add Students";
        popup(title);

        // Testo nel popup
        // DropDown Course and Class
        DrawText("In Course", popupX + 30, popupY + 270, 20,
                 GetColor(textColor));
        DrawText("In Class", popupX + 350, popupY + 270, 20,
                 GetColor(textColor));

        // Name and Id Student
        DrawText("Students Name", popupX + 30, popupY + 140, 20,
                 GetColor(textColor));
        GuiTextBox({(float)popupX + 200, (float)popupY + 130, 300, 40},
                   userInputAddStudentsName, 255, !focusOnId);
        DrawText("Students Id", popupX + 30, popupY + 210, 20,
                 GetColor(textColor));
        GuiTextBox({(float)popupX + 200, (float)popupY + 200, 300, 40},
                   userInputAddStudentsId, 255, !focusOnId);

        // Controll mouse
        controllMouse(popupX, popupY);

        // Pulsante "Chiudi" nel popup
        buttonEsc(isPopupOpen);

        int StudentId = charInt(userInputAddStudentsId);
        int ClassId = charInt(userInputAddClassesId);

        if (StudentId == -1)
        {
            DrawText("Invalid Student ID", popupX + 30, popupY + 340, 20, RED);
            canSave = false;
        }
        else if (studentExists(StudentId, userInputAddClassesName) || !isValidStudentName(userInputAddClassesName))
        {
            if (studentExists(StudentId, userInputAddClassesName))
                DrawText("Course already exists", popupX + 30, popupY + 340, 20,
                         RED);

            if (!isValidStudentName(userInputAddClassesName))
                DrawText("Invalid name. (3-50 char)", popupX + 30, popupY + 340, 20,
                         RED);

            canSave = false;
        }
        else
            canSave = true;

        // Pulsante "Salva" nel popup
        if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40},
                      "Save"))
        {
            if (canSave)
            {
                writeNewStudent(ClassId, userInputAddStudentsId, userInputAddClassesName);
                strcpy(userInputAddClassesName, "");
                strcpy(userInputAddStudentsId, "");
                StudentId = 0;
                ClassId = 0;
                isPopupOpen = false; // Chiudi il popup
            }
        }
    }
}

// Button add icon
void popupAddIconClasses(bool &isPopupOpen, bool &quit)
{
    // Disegna il popup se è aperto
    if (isPopupOpen)
    {
        const char *title = "Add Classes";
        popup(title);

        // Testo nel popup
        // Name
        DrawText("Classes Name", popupX + 30, popupY + 140, 20,
                 GetColor(textColor));
        GuiTextBox({(float)popupX + 200, (float)popupY + 130, 300, 40},
                   userInputAddClassesName, 255, !focusOnId);

        // Controll mouse
        controllMouse(popupX, popupY);

        // Pulsante "Chiudi" nel popup
        buttonEsc(isPopupOpen);

        if (classExists(userInputAddCourseId, userInputAddClassesName) || !isValidClassName(userInputAddClassesName))
        {
            if (classExists(userInputAddCourseId, userInputAddClassesName))
                DrawText("Course already exists", popupX + 30, popupY + 275, 20,
                         RED);

            if (!isValidClassName(userInputAddClassesName))
                DrawText("Invalid name. (3-50 char)", popupX + 30, popupY + 275, 20,
                         RED);

            canSave = false;
        }
        else
            canSave = true;

        // Pulsante "Salva" nel popup
        if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40},
                      "Save"))
        {
            if (canSave)
            {
                writeNewClass(userInputAddCourseId, userInputAddClassesName);
                strcpy(userInputAddClassesName, "");
                userInputAddCourseId = 0;
                isPopupOpen = false; // Chiudi il popup
            }
        }
    }
}
void popupAddIconStudents(bool &isPopupOpen, bool &quit)
{
    // Disegna il popup se è aperto
    if (isPopupOpen)
    {
        const char *title = "Add Students";
        popup(title);

        // Testo nel popup
        // DropDown Course and Class
        DrawText("In Course", popupX + 30, popupY + 270, 20,
                 GetColor(textColor));

        // Name and Id Student
        DrawText("Students Name", popupX + 30, popupY + 140, 20,
                 GetColor(textColor));
        GuiTextBox({(float)popupX + 200, (float)popupY + 130, 300, 40},
                   userInputAddStudentsName, 255, !focusOnId);
        DrawText("Students Id", popupX + 30, popupY + 210, 20,
                 GetColor(textColor));
        GuiTextBox({(float)popupX + 200, (float)popupY + 200, 300, 40},
                   userInputAddStudentsId, 255, !focusOnId);

        // Controll mouse
        controllMouse(popupX, popupY);

        // Pulsante "Chiudi" nel popup
        buttonEsc(isPopupOpen);

        int StudentId = charInt(userInputAddStudentsId);
        int ClassId = charInt(userInputAddClassesId);

        if (StudentId == -1)
        {
            DrawText("Invalid Student ID", popupX + 30, popupY + 340, 20, RED);
            canSave = false;
        }
        else if (studentExists(StudentId, userInputAddClassesName) || !isValidStudentName(userInputAddClassesName))
        {
            if (studentExists(StudentId, userInputAddClassesName))
                DrawText("Course already exists", popupX + 30, popupY + 340, 20,
                         RED);

            if (!isValidStudentName(userInputAddClassesName))
                DrawText("Invalid name. (3-50 char)", popupX + 30, popupY + 340, 20,
                         RED);

            canSave = false;
        }
        else
            canSave = true;

        // Pulsante "Save" nel popup
        if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40},
                      "Save"))
        {
            if (canSave)
            {
                writeNewStudent(ClassId, userInputAddStudentsId, userInputAddClassesName);
                strcpy(userInputAddClassesName, "");
                strcpy(userInputAddStudentsId, "");
                StudentId = 0;
                ClassId = 0;
                isPopupOpen = false; // Chiudi il popup
            }
        }
    }
}

// Button Delete
void popupDeleteCourses(bool &isPopupOpen, bool &quit)
{
    // Disegna il popup se è aperto
    if (isPopupOpen)
    {
        const char *title = "Delete Courses";
        popup(title);

        DrawText("Are you sure", popupX + 30, popupY + 140, 20,
                 GetColor(textColor));

        // variabile da usare userInputDeleteCourses

        // Pulsante "Chiudi" nel popup
        buttonEsc(isPopupOpen);

        // Pulsante "Delete" nel popup
        if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40},
                      "Delete"))
        {
            if (canDelete)
            {
                // funzione elimina
                strcpy(userInputDeleteCourses, "");
                isPopupOpen = false; // Chiudi il popup
            }
        }
    }
}
void popupDeleteClasses(bool &isPopupOpen, bool &quit)
{
    // Disegna il popup se è aperto
    if (isPopupOpen)
    {
        const char *title = "Delete Classes";
        popup(title);

        DrawText("Are you sure", popupX + 30, popupY + 140, 20,
                 GetColor(textColor));

        // variabile da usare userInputDeleteClasses

        // Pulsante "Chiudi" nel popup
        buttonEsc(isPopupOpen);

        // Pulsante "Delete" nel popup
        if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40},
                      "Delete"))
        {
            if (canDelete)
            {
                // funzione elimina
                strcpy(userInputDeleteClasses, "");
                isPopupOpen = false; // Chiudi il popup
            }
        }
    }
}
void popupDeleteStudents(bool &isPopupOpen, bool &quit)
{
    // Disegna il popup se è aperto
    if (isPopupOpen)
    {
        const char *title = "Delete Students";
        popup(title);

        DrawText("Are you sure", popupX + 30, popupY + 140, 20,
                 GetColor(textColor));

        // variabile da usare userInputDeleteStudents

        // Pulsante "Chiudi" nel popup
        buttonEsc(isPopupOpen);

        // Pulsante "Delete" nel popup
        if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40},
                      "Delete"))
        {
            if (canDelete)
            {
                // funzione elimina
                strcpy(userInputDeleteStudents, "");
                isPopupOpen = false; // Chiudi il popup
            }
        }
    }
}

// Button Edit
// void popupEditCourses(bool &isPopupOpen, bool &quit);
// void popupEditClasses(bool &isPopupOpen, bool &quit);
// void popupEditStudents(bool &isPopupOpen, bool &quit);

// Add Vote
void popupAddVoteClasses(bool &isPopupOpen, bool &quit)
{
    // Disegna il popup se è aperto
    if (isPopupOpen)
    {
        const char *title = "Add Vote";
        popup(title);

        // Testo nel popup
        DrawText("Vote out of thirty, for the entire Classes", popupX + 30, popupY + 140, 20,
                 GetColor(textColor));
        DrawText("Vote", popupX + 30, popupY + 210, 20,
                 GetColor(textColor));
        GuiTextBox({(float)popupX + 200, (float)popupY + 130, 300, 40},
                   userInputAddVoteClasses, 255, true);

        // variabile da usare userInputAddVoteClasses

        // Pulsante "Chiudi" nel popup
        buttonEsc(isPopupOpen);

        // Pulsante "Save" nel popup
        if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40},
                      "Save"))
        {
            if (canSave)
            {
                // funzione voto insert Classes
                strcpy(userInputAddVoteClasses, "");
                isPopupOpen = false; // Chiudi il popup
            }
        }
    }
}
void popupAddVoteStudents(bool &isPopupOpen, bool &quit)
{
    // Disegna il popup se è aperto
    if (isPopupOpen)
    {
        const char *title = "Add Vote Students";
        popup(title);

        // Testo nel popup
        DrawText("Vote out of thirty, for the entire Students", popupX + 30, popupY + 140, 20,
                 GetColor(textColor));
        DrawText("Vote", popupX + 30, popupY + 210, 20,
                 GetColor(textColor));
        GuiTextBox({(float)popupX + 200, (float)popupY + 130, 300, 40},
                   userInputAddVoteStudents, 255, true);

        // variabile da usare userInputAddVoteStudents

        // Pulsante "Chiudi" nel popup
        buttonEsc(isPopupOpen);

        // Pulsante "Save" nel popup
        if (GuiButton((Rectangle){popupX + 475, popupY + 340, 100, 40},
                      "Save"))
        {
            if (canSave)
            {
                // funzione voto insert Students
                strcpy(userInputAddVoteStudents, "");
                isPopupOpen = false; // Chiudi il popup
            }
        }
    }
}
