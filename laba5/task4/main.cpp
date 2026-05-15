// main.cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "config.h"

using namespace std;

// Функция для обработки команды NEW_STUDENTS
void new_students(int number) {
    if (number > 0) {
        total_students += number;
        cout << "Добавлено " << number << " студентов" << endl;
    }
    else if (number < 0) {
        int to_remove = -number;
        
        // Собираем список кандидатов на отчисление (не неприкасаемых)
        vector<int> candidates;
        for (int i = 1; i <= total_students; i++) {
            if (is_suspicious[i] && !is_immortal[i]) {
                candidates.push_back(i);
            }
        }
        
        if (candidates.empty()) {
            cout << "Ошибка: Нет кандидатов на отчисление" << endl;
            return;
        }
        
        if (to_remove > candidates.size()) {
            cout << "Ошибка: невозможно отчислить больше студентов, чем есть их в списках на отчисление" << endl;
            return;
        }
        
        // Удаляем первых  кандидатов
        for (int i = 0; i < to_remove; i++) {
            is_suspicious[candidates[i]] = false;
            is_immortal[candidates[i]] = false;
        }
        
        cout << "Удалено " << to_remove << " студентов" << endl;
    }
}


void suspicious(int student_num) {
    if (student_num < 1 || student_num > total_students) {
        cout << "Ошибка: Студент " << student_num << " не существует" << endl;
        return;
    }
    
    if (is_suspicious[student_num]) {
        cout << "Ошибка: Студент " << student_num << " уже является кандидатом на отчисление" << endl;
        return;
    }
    
    is_suspicious[student_num] = true;
    is_immortal[student_num] = false;
    cout << "Студент " << student_num << " стал кандидатом на отчисление" << endl;
}


void immortal(int student_num) {
    if (student_num < 1 || student_num > total_students) {
        cout << "Ошибка: Студент " << student_num << " не существует" << endl;
        return;
    }
    
    if (!is_suspicious[student_num]) {
        cout << "Ошибка: Студент " << student_num << " не может стать неприкасаемым, поскольку он не находится в списках на отчисление" << endl;
        return;
    }
    
    is_immortal[student_num] = true;
    cout << "Студент " << student_num << " стал неприкасаемым" << endl;
}


void top_list() {
    vector<int> candidates;
    for (int i = 1; i <= total_students; i++) {
        if (is_suspicious[i] && !is_immortal[i]) {
            candidates.push_back(i);
        }
    }
    
    if (candidates.empty()) {
        cout << "Список студентов на отчисление: нет" << endl;
    } else {
        cout << "Список студентов на отчисление: ";
        for (size_t i = 0; i < candidates.size(); i++) {
            cout << "Студент " << candidates[i];
            if (i < candidates.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

int main() {
    int N;
    cout << "Введите количество запросов (N):" << endl;
    cout << ">>> ";
    cin >> N;
    
    for (int i = 0; i < N; i++) {
        string command;
        cout << ">>> ";
        cin >> command;
        
        if (command == "NEW_STUDENTS") {
            int number;
            cin >> number;
            new_students(number);
        }
        else if (command == "SUSPICIOUS") {
            int student_num;
            cin >> student_num;
            suspicious(student_num);
        }
        else if (command == "IMMORTAL") {
            int student_num;
            cin >> student_num;
            immortal(student_num);
        }
        else if (command == "TOP-LIST") {
            top_list();
        }
        else {
            cout << "Неизвестная команда" << endl;
            // Пропускаем оставшуюся часть строки
            string rest;
            getline(cin, rest);
        }
    }
    
    return 0;
}