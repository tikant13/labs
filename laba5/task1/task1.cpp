#include <iostream>
#include "config.h"
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

map<string, string> cellProduct;  // адрес и наименование товара
map<string, int> cellQuantity;    // адрес и количество товара

// Функция для генерации адреса ячейки
string generateAddress(char zone, int shelf, int section, int shelfLevel) { // функция для генерации адреса ячейки
    return string(1, zone) + to_string(shelf) + to_string(section) + to_string(shelfLevel);
}


void initializeWarehouse() { // инициализации всех ячеек склада
    for (int z = 0; z < ZONA; z++) {
        for (int shelf = 1; shelf <= STEL; shelf++) {
            for (int section = 1; section <= SECTIONS; section++) {
                for (int level = 1; level <= POLKI; level++) {
                    string address = generateAddress(ZONES[z], shelf, section, level);
                    cellProduct[address] = "";
                    cellQuantity[address] = 0;
                }
            }
        }
    }
}


bool isValidAddress(const string& address) { // проверяем существует ли ячейка
    return cellProduct.find(address) != cellProduct.end();
}


void addProduct(const string& productName, int quantity, const string& address) { 
    
    if (!isValidAddress(address)) { // проверка существования адреса
        cout << "Ошибка: Неверный адрес ячейки " << address << endl;
        return;
    }
    
   
    if (cellProduct[address] != "" && cellProduct[address] != productName) {  // проверка, не занята ли ячейка другим товаром
        cout << "Ошибка: Ячейка " << address << " занята товаром " << cellProduct[address] << endl;
        return;
    }
    
    
    if (cellQuantity[address] + quantity > CAPACITY) { // проверка превышения вместимости
        cout << "Ошибка: Превышена вместимость ячейки (максимум " << CAPACITY << ")" << endl;
        return;
    }
    
   
    if (cellProduct[address] == "") { // добавление товара
        cellProduct[address] = productName;
    }
    cellQuantity[address] += quantity;
    cout << "Добавлено " << quantity << " " << productName << " в " << address << endl;
}


void removeProduct(const string& productName, int quantity, const string& address) {
    
    if (!isValidAddress(address)) {
        cout << "Ошибка: Неверный адрес ячейки " << address << endl;
        return;
    }
    
    if (cellProduct[address] == "") {
        cout << "Ошибка: Товар " << productName << " не найден в ячейке " << address << endl;
        return;
    }
    
    if (cellProduct[address] != productName) {
        cout << "Ошибка: Товар " << productName << " не найден в ячейке " << address << endl;
        return;
    }
    

    if (cellQuantity[address] < quantity) {
        cout << "Ошибка: Недостаточно товаров для удаления (доступно: " << cellQuantity[address] << ")" << endl;
        return;
    }
    
    cellQuantity[address] -= quantity; // Удаление товара
    int remaining = cellQuantity[address];
    
    if (remaining == 0) {
        cellProduct[address] = "";
        cout << "Удалено " << quantity << " " << productName << " (ячейка освобождена)" << endl;
    } else {
        cout << "Удалено " << quantity << " " << productName << " (остаток: " << remaining << ")" << endl;
    }
}


int countOccupiedCells() { // функция для подсчета занятых ячеек
    int occupied = 0;
    for (const auto& pair : cellProduct) {
        if (pair.second != "") {
            occupied++;
        }
    }
    return occupied;
}


int calculateLoadInUnits() { // функция для подсчета заполненности в единицах товара
    int totalUnits = 0;
    for (const auto& pair : cellQuantity) {
        totalUnits += pair.second;
    }
    return totalUnits;
}


void showInfo() {
    int totalOccupiedCells = countOccupiedCells();
    int totalUnits = calculateLoadInUnits();
    int totalCells = ZONA * STEL * SECTIONS * POLKI;
    
    
    double overallLoadPercent = (double)totalUnits / TOTAL * 100; // Общая загруженность склада в процентах
    
    cout << fixed << setprecision(2);
    cout << "Загруженность склада: " << overallLoadPercent << " %" << endl;
    cout << endl;
    
    // Загруженность по зонам
    for (int z = 0; z < ZONA; z++) {
        char zone = ZONES[z];
        int zoneUnits = 0;
        int zoneCapacity = STEL * SECTIONS * POLKI * CAPACITY;
        
        for (int shelf = 1; shelf <= STEL; shelf++) {
            for (int section = 1; section <= SECTIONS; section++) {
                for (int level = 1; level <= POLKI; level++) {
                    string address = generateAddress(zone, shelf, section, level);
                    zoneUnits += cellQuantity[address];
                }
            }
        }
        
        double zoneLoadPercent = (double)zoneUnits / zoneCapacity * 100;
        cout << "Загруженность зоны " << zone << ": " << zoneLoadPercent << " %" << endl;
    }
    
    cout << endl;
    
    
    cout << "Заполненные ячейки:" << endl;
    vector<string> occupiedAddresses;
    
    for (int z = 0; z < ZONA; z++) {
        for (int shelf = 1; shelf <= STEL; shelf++) {
            for (int section = 1; section <= SECTIONS; section++) {
                for (int level = 1; level <= POLKI; level++) {
                    string address = generateAddress(ZONES[z], shelf, section, level);
                    if (cellProduct[address] != "") {
                        cout << address << ": " << cellProduct[address] << " (" << cellQuantity[address] << ")" << endl;
                    }
                }
            }
        }
    }
    
    cout << endl;
    
    
    cout << "Пустые ячейки:" << endl;
    vector<string> emptyAddresses;
    
    for (int z = 0; z < ZONA; z++) {
        for (int shelf = 1; shelf <= STEL; shelf++) {
            for (int section = 1; section <= SECTIONS; section++) {
                for (int level = 1; level <= POLKI; level++) {
                    string address = generateAddress(ZONES[z], shelf, section, level);
                    if (cellProduct[address] == "") {
                        emptyAddresses.push_back(address);
                    }
                }
            }
        }
    }
    
    if (emptyAddresses.empty()) {
        cout << "(нет пустых ячеек)" << endl;
    } else {
        // Выводим пустые ячейки по 10 в строке
        for (size_t i = 0; i < emptyAddresses.size(); i++) {
            cout << emptyAddresses[i];
            if ((i + 1) % 10 == 0 && i != emptyAddresses.size() - 1) {
                cout << endl;
            } else if (i != emptyAddresses.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

// Функция для разбора команды
void processCommand(const string& command) {
    istringstream iss(command);
    string cmd;
    iss >> cmd; // извлекаем первое слово (команду)
    
    if (cmd == "ADD" || cmd == "add") {
        string productName;
        int quantity;
        string address;
        
        
        iss >> productName >> quantity >> address;
        
        if (productName.empty() || quantity <= 0 || address.empty()) {
            cout << "Неверный формат команды ADD" << endl;
            return;
        }
        
        addProduct(productName, quantity, address);
    }
    else if (cmd == "REMOVE" || cmd == "remove") {
        string productName;
        int quantity;
        string address;
        
        iss >> productName >> quantity >> address;
        
        if (productName.empty() || quantity <= 0 || address.empty()) {
            cout << "Ошибка: Неверный формат команды REMOVE" << endl;
            return;
        }
        
        removeProduct(productName, quantity, address);
    }
    else if (cmd == "INFO" || cmd == "info") {
        showInfo();
    }
    else {
        cout << "Неизвестная команда. Используйте: ADD, REMOVE, INFO" << endl;
    }
}

int main() {
    cout << "--- Учёт товаров на складе ---" << endl;
    cout << "Характеристика склада: 1 зона, 19 стеллажей, 5 секций, 3 полки" << endl;
    cout << "Общая вместимость: " << TOTAL << endl;
    cout << "Максимум товара в ячейке: " << CAPACITY << endl;
    cout << endl;
    
    initializeWarehouse();
    
    string input;
    while (true) {
        cout << ">>> ";
        getline(cin, input); // читаем всю строку 
        
        if (input.empty()) {
            continue;
        }
        
        processCommand(input);
        cout << endl;
    }
    
    return 0;
}