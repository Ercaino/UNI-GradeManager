#ifndef POPUPS_H
#define POPUPS_H
#include <raylib.h>

// Button add
void popupAddCourses(bool &, bool &);
void popupAddClasses(bool &isPopupOpen, bool &quit, Rectangle &panelRec,
                     Rectangle &panelContentRec, Rectangle &panelView,
                     Vector2 &panelScroll);
void popupAddStudents(bool &isPopupOpen, bool &quit, Rectangle &panelRec,
                      Rectangle &panelContentRec, Rectangle &panelView,
                      Vector2 &panelScroll);

void popupAddIconClasses(bool &, bool &);
void popupAddIconStudents(bool &, bool &);

// Button Delete
void popupDeleteCourses(bool &, bool &);
void popupDeleteClasses(bool &, bool &);
void popupDeleteStudents(bool &, bool &);

// Button Edit
// void popupEditCourses(bool &, bool &);
// void popupEditClasses(bool &, bool &);
// void popupEditStudents(bool &, bool &);

// Add Vote
void popupAddVoteClasses(bool &, bool &);
void popupAddVoteStudents(bool &, bool &);

#endif
