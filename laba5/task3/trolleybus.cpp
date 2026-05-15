#include "trol.h"

map<string, vector<string>> trolleybuses;

void printError(const string& message) {
    cout << "Ошибка: " << message << endl;
}

void create_trl(const vector<string>& parts) {
    if (parts.size() < 4) {
        printError("Недостаточно аргументов");
        return;
    }
    
    string trl_name = parts[1];
    
    // Проверяем, что N - число (простая проверка)
    string n_str = parts[2];
    for (char c : n_str) {
        if (!isdigit(c)) {
            printError("N должно быть числом");
            return;
        }
    }
    int n = stoi(n_str);
    
    if (parts.size() < 3 + n) {
        printError("Недостаточно остановок");
        return;
    }
    
    vector<string> stops;
    for (int i = 0; i < n; i++) {
        stops.push_back(parts[3 + i]);
    }
    
    // Проверки
    if (trolleybuses.find(trl_name) != trolleybuses.end()) {
        printError("Троллейбус с именем " + trl_name + " уже создан");
        return;
    }
    
    if (stops.size() < 2) {
        printError("Троллейбус не может быть создан с одной остановкой");
        return;
    }
    
    // Проверка на одинаковые остановки
    for (size_t i = 0; i < stops.size(); i++) {
        for (size_t j = i + 1; j < stops.size(); j++) {
            if (stops[i] == stops[j]) {
                printError("Троллейбус не может быть создан с двумя одинаковыми остановками");
                return;
            }
        }
    }
    
    trolleybuses[trl_name] = stops;
    cout << "Троллейбус " << trl_name << " создан" << endl;
}

void trls_in_stop(const vector<string>& parts) {
    if (parts.size() != 2) {
        printError("Неверное количество аргументов");
        return;
    }
    
    string stop_name = parts[1];
    vector<string> found;
    
    // Перебираем все троллейбусы
    for (auto it = trolleybuses.begin(); it != trolleybuses.end(); it++) {
        vector<string> stops = it->second;
        // Ищем остановку в маршруте
        for (size_t i = 0; i < stops.size(); i++) {
            if (stops[i] == stop_name) {
                found.push_back(it->first);
                break;
            }
        }
    }
    
    if (found.empty()) {
        printError("Остановка " + stop_name + " не найдена");
    } else {
        cout << "Троллейбусы на остановке " << stop_name << ": ";
        for (size_t i = 0; i < found.size(); i++) {
            if (i > 0) cout << ", ";
            cout << found[i];
        }
        cout << endl;
    }
}

void stops_in_trl(const vector<string>& parts) {
    if (parts.size() != 2) {
        printError("Неверное количество аргументов");
        return;
    }
    
    string trl_name = parts[1];
    
    if (trolleybuses.find(trl_name) == trolleybuses.end()) {
        printError("Троллейбус " + trl_name + " не найден");
        return;
    }
    
    vector<string> stops = trolleybuses[trl_name];
    
    cout << "Остановки троллейбуса " << trl_name << ": ";
    for (size_t i = 0; i < stops.size(); i++) {
        if (i > 0) cout << " ";
        cout << stops[i];
    }
    cout << endl;
    
    // Для каждой остановки выводим другие троллейбусы
    for (size_t i = 0; i < stops.size(); i++) {
        string stop = stops[i];
        vector<string> other_trl;
        
        // Ищем другие троллейбусы на этой остановке
        for (auto it = trolleybuses.begin(); it != trolleybuses.end(); it++) {
            if (it->first != trl_name) {
                vector<string> trl_stops = it->second;
                for (size_t j = 0; j < trl_stops.size(); j++) {
                    if (trl_stops[j] == stop) {
                        other_trl.push_back(it->first);
                        break;
                    }
                }
            }
        }
        
        cout << "Остановка " << stop << ": ";
        if (other_trl.empty()) {
            cout << "-";
        } else {
            for (size_t j = 0; j < other_trl.size(); j++) {
                if (j > 0) cout << ", ";
                cout << other_trl[j];
            }
        }
        cout << endl;
    }
}

void trls(const vector<string>& parts) {
    if (trolleybuses.empty()) {
        printError("Троллейбусы не найдены");
        return;
    }
    
    for (auto it = trolleybuses.begin(); it != trolleybuses.end(); it++) {
        cout << "Троллейбус " << it->first << ": ";
        vector<string> stops = it->second;
        for (size_t i = 0; i < stops.size(); i++) {
            if (i > 0) cout << " ";
            cout << stops[i];
        }
        cout << endl;
    }
}