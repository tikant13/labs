#include "trol.h"

int main() {
    cout << "Система управления троллейбусами" << endl;
    
    string input;
    while (true) {
        cout << ">>> ";
        getline(cin, input);
        
        if (input.empty()) {
            continue;
        }
        
        // Разбиваем строку на части
        vector<string> parts;
        stringstream ss(input);
        string part;
        while (ss >> part) {
            parts.push_back(part);
        }
        
        if (parts.empty()) continue;
        
        string cmd = parts[0];
        
        if (cmd == "CREATE_TRL" || cmd == "create_trl") {
            create_trl(parts);
        }
        else if (cmd == "TRLS_IN_STOP" || cmd == "trls_in_stop") {
            trls_in_stop(parts);
        }
        else if (cmd == "STOPS_IN_TRL" || cmd == "stops_in_trl") {
            stops_in_trl(parts);
        }
        else if (cmd == "TRLS" || cmd == "trls") {
            trls(parts);
        }
        else {
            cout << "Не распознано" << endl;
        }
    }
    
    return 0;
}