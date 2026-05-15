#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "config.h"

using namespace std;

void Enque(const int& windows, const string& command){
    istringstream iss(command);
    string cmd;
    int time;
    iss >> cmd >> time;

    // формируем номер талона
    string ticket = "T";
    if (ticketCounter < 10) ticket += "00";
    else if (ticketCounter < 100) ticket += "0";
    ticket += to_string(ticketCounter);
    
    // сохраняем посетителя
    globalTickets.push_back(ticket);
    globalTimes.push_back(time);
    ticketCounter++;
    
    cout << ticket << endl;


}

void Distribute(int windows) {
    // Векторы для хранения информации об окнах
    vector<int> windowTimes(windows, 0); // общее время каждого окна
    vector<vector<string>> windowTickets(windows); // списки талонов для каждого окна
    
    // Распределяем каждого посетителя
    for (size_t i = 0; i < globalTickets.size(); i++) {
        int bestWindow = 0;
        int minTime = windowTimes[0];
        
        // Ищем окно с минимальной итоговой загрузкой
        for (int j = 1; j < windows; j++) {
            if (windowTimes[j] < minTime) {
                minTime = windowTimes[j];
                bestWindow = j;
            }
        }
        
        // Добавляем посетителя в выбранное окно
        windowTimes[bestWindow] += globalTimes[i];
        windowTickets[bestWindow].push_back(globalTickets[i]);
    }
    
    // Выводим результаты
    for (int i = 0; i < windows; i++) {
        cout << "    Окно " << (i + 1) << " (" << windowTimes[i] << " минут): ";
        for (size_t j = 0; j < windowTickets[i].size(); j++) {
            cout << windowTickets[i][j];
            if (j < windowTickets[i].size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}


int main(){
    cout << "Введите количество окон:"<<endl<<">>> ";
    int windows;
    cin >> windows;

    cin.ignore(); // чтобы не считывала сразу пустую строку

    string input;
    while (true){
        cout << ">>> ";
        getline(cin, input);

        if (input.empty()){
            continue;
        }
        if (input == "DISTRIBUTE" || input =="distribute"){
            Distribute(windows);
            break;
        }
        if (input.find("ENQUEUE") == 0 || input.find("enqueue") == 0 ){
            Enque(windows, input);
        } else {
            cout << "Не распознано"<< endl;
        }


    }
    
    return 0;
}