#include <iostream>
#include <vector>
using namespace std;

int main() {

    int n;
    int m;
    cin >> n >> m;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // Префиксные суммы
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + a[i];
    }
    
    int pavelScore = 0, vikaScore = 0;
    int pos = 0;
    int lastPavel = -1;  // сколько взял Павел в прошлый раз
    int lastVika = -1;   // сколько взяла Вика в прошлый раз
    int turn = 0; // 0  Павел, 1  Вика
    
    while (pos < n) {
        int maxTake = min(m, n - pos);
        int forbidden = -1;
        
        if (turn == 0) { //нельзя взять столько, сколько взял в свой предыдущий ход
            forbidden = lastPavel;
        } else {
            forbidden = lastVika;
        }
        
        int bestSum = -1;
        int bestTake = 1;
        
        for (int take = 1; take <= maxTake; take++) {
            if (take == forbidden) continue;
            
            int sum = prefix[pos + take] - prefix[pos];
            
            if (sum > bestSum || (sum == bestSum && take < bestTake)) {
                bestSum = sum;
                bestTake = take;
            }
        }
        
        if (turn == 0) {
            pavelScore += bestSum;
            lastPavel = bestTake;
        } else {
            vikaScore += bestSum;
            lastVika = bestTake;
        }
        
        pos += bestTake;
        turn = 1 - turn;
    }
    
    if (pavelScore > vikaScore) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }
    
    return 0;
}