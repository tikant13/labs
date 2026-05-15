#ifndef TROL_H
#define TROL_H

#include <iostream>
using namespace std;

// Глобальные списки
const int MAX_STUDENTS = 1000;
bool is_suspicious[MAX_STUDENTS] = {false};  // кандидаты на отчисление
bool is_immortal[MAX_STUDENTS] = {false};    // неприкасаемые
int total_students = 0;                      // общее количество студенто

#endif