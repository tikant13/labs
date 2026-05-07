#include <iostream>
#include <vector>
#include <string>

using namespace std;

void input(int& n, int& m, vector<string>& candidates, vector<int>& voters, vector<vector<int>>& ranking){

    cout << "Введите имена кандидатов"<<endl;
    for (int i = 0; i < n; i++) {
        cin >> candidates[i];
    }
    
    cout << "Для каждой группы сначала количество избирателей"<<endl;
    cout << "затем порядок кандидатов (от лучшего к худшему)"<<endl;

    for (int i = 0; i < m; i++) {
        cout << "Группа " << i + 1 << ":\n";

        cin >> voters[i]; // количество избирателей в группе

        for (int j = 0; j < n; j++) { // порядок кандидатов
            cin >> ranking[i][j];
            ranking[i][j]--; // чтобы начаналось с 0
        }
    }

}

int main() {
    int n, m;

    cout << "Количество кандидатов ";
    cin >> n;

    cout << "Количество групп избирателей ";
    cin >> m;

    vector<string> candidates(n);
    vector<int> voters(m);
    vector<vector<int>> ranking(m, vector<int>(n));
    input(n, m, candidates, voters, ranking);
    

    vector<int> borda(n, 0); // очки кандидатов
    
    for (int i = 0; i < m; i++) { // проходимся по группам
        for (int pos = 0; pos < n; pos++) { // проходимся по позициям кандидатам
            int candidate = ranking[i][pos];
            borda[candidate] += (n - pos - 1) * voters[i]; // начисление очков 
        }
    }

    int bordaWinner = 0;

    for (int i = 1; i < n; i++) { // ищем кандидата с максимальным числом очков
        if (borda[i] > borda[bordaWinner]) {
            bordaWinner = i;
        }
    }



    int condorcetWinner = -1;

    for (int a = 0; a < n; a++) {
        bool winsAll = true; // считаем, что кандидат побеждает всех

        for (int b = 0; b < n; b++) {
            if (a == b) continue;

            int votesA = 0;
            int votesB = 0;

            for (int g = 0; g < m; g++) {

                int posA = 0, posB = 0;

                for (int k = 0; k < n; k++) {
                    if (ranking[g][k] == a) {
                        posA = k;
                    }
                    if (ranking[g][k] == b) {
                        posB = k;
                    }
                }

                if (posA < posB)
                    votesA += voters[g];
                else
                    votesB += voters[g];
            }

            if (votesA <= votesB) {
                winsAll = false;
                break;
            }
        }

        if (winsAll) {
            condorcetWinner = a;
            break;
        }
    }


    cout << endl<<"Метод Борда "<<endl;

    for (int i = 0; i < n; i++) {
        cout << candidates[i] << ": " << borda[i] << " очков"<<endl;
    }

    cout << "Победитель: " << candidates[bordaWinner] <<" очков "<< borda[bordaWinner] << endl;

    cout <<endl<< "Метод Кондорсе"<<endl;

    if (condorcetWinner == -1)
        cout << "Победитель не определён"<<endl;
    else
        cout << "Победитель: " << candidates[condorcetWinner] << endl;

    return 0;
}