#include<iostream>
#include<vector>
#include<cstdint>
#include<math.h>

using namespace std;

int NOD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mod(int base, int power, int modulo){ 
    base %= modulo;
    power %= modulo-1;
    int result = 1;
    for (int i = 0; i < power; ++i){
        result *=base;
        result %=modulo;
    }
    return result;
}

vector<int> gener(int p, int q, int M, int x, int c) {
    vector<int> sequence;
    if (NOD(x, M) != 1) { // проверяем, что x взаимно простое с M
        cout << "Ошибка!!! x должно быть взаимно простым с M!!!" << endl;
        return sequence;
    }
    
   
    int x0 = (x * x) % M; // Вычисляем x0
    
    
    for (int n = 0; n < c; ++n) { // генерируем последовательность
        
        int ex = mod(2, n, (p - 1) * (q - 1)); // Используем формулу: x_n = x0^(2^n mod ((p-1)(q-1))) mod M
        int xn = mod(x0, ex, M);
        sequence.push_back(xn);
    }
    
    return sequence;
}

int main(){
    int p, q, M, x, c;
    cin >> p >> q >>M >> x >> c;
    vector<int> seq1 = gener(p, q, M, x, c);
    for (int i : seq1) {
        cout << i << " ";
    }
    cout << endl;
    
    return 0;

}