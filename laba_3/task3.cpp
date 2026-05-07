#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


int64_t nod(int64_t a, int64_t b) { //НОД
    while (b != 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {

    int64_t a;
    int64_t b;
    cin >> a >> b;

    
    if (b <= 1) { // если ряд расходится
        cout << "infinity" << endl;
        return 0;
    }

    
    double sum = 0; // накопленная сумма ряда
    double term = 0; //текущее слагаемое
    
    for (int64_t n = 1; n <= 1000; n++) { // вычисляем сумму ряда

        double numerator = 1;
        for (int64_t i = 0; i < a; i++) {  // Вычисляем n^a
            numerator *= n;
        }
        
       
        double denominator = 1;
        for (int64_t i = 0; i < n; i++) {  // Вычисляем b^n
            denominator *= b;
        }
        
        term = numerator / denominator;
        sum += term;
        
        // Если слагаемое стало очень маленьким, останавливаемся
        if (term < 1e-15) {
            break;
        }
    }

    
    int64_t bestNum = 1;
    int64_t bestDen = 1;
    double bestDiff = 1e18;
    
    
    for (int64_t den = 1; den <= 10000; den++) { // перебираем знаменатели, чтобы найти лучший
        // Находим ближайший числитель
        int64_t num = (int64_t)(sum * den + 0.5);
        
        // Проверяем насколько близко
        double diff = abs((double)num / den - sum);
        
        if (diff < bestDiff) {
            bestDiff = diff;
            bestNum = num;
            bestDen = den;
        }
    }

    // Сокращаем дробь
    int64_t common = nod(bestNum, bestDen);
    cout << bestNum / common << "/" << bestDen / common << endl;

    return 0;
}