#ifndef TROL_H
#define TROL_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Глобальное хранилище троллейбусов
extern map<string, vector<string>> trolleybuses;

// функции для работы с троллейбусами
void create_trl(const vector<string>& parts);
void trls_in_stop(const vector<string>& parts);
void stops_in_trl(const vector<string>& parts);
void trls(const vector<string>& parts);
void printError(const string& message);

#endif