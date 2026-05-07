#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <cstdint>

using namespace std;


vector<int> sieveErat() { // решето эратосфена

   vector<bool> sieveBool(5000, true);
    sieveBool[0] = sieveBool[1] = false;
    for (int i = 2; i * i <= 5000; ++i)
        if (sieveBool[i])
            for (int j = i * i; j <= 5000; j += i)
                sieveBool[j] = false;

    vector<int> sieve; 

    for (int i = 2; i <= 5000; ++i)
        if (sieveBool[i] == true) {
            sieve.push_back(i);
        }

    return sieve;

}


uint64_t powN( uint64_t a, uint64_t degree, uint64_t p) { // возведение в степень
    
    uint64_t res = 1;

    a %= p;
    while (degree > 0) {
        if (degree % 2 == 1) {
            res = (res * a) % p;
        }
        a = (a * a) % p;
        degree /= 2;
    }
    return res;
}


pair<uint64_t, uint64_t> generateGost(int t, const vector<int>& sieve) { //генерация простого числа ГОСТ

    int k = (t + 1) / 2; // разрядность q округление вверх

    // Выбор q из таблицы
    vector<int> candidates;
    for (int x : sieve) {
        if (x >= (1 << (k - 1)) && x < (1 << k))
            candidates.push_back(x);
    }

    while (true) {
        int q = candidates[rand() % candidates.size()];
        
        
        double xi = (double)rand() / RAND_MAX; // генерация случайной велечины

        // вычисем N по форуле 
        uint64_t t1 = (uint64_t)1 << (t - 1);
        uint64_t N = (t1) / q;
        N += ((uint64_t)(t1 * xi)) / q;
        
        // если N нечётное, то N+=1
        if (N % 2 != 0) {
            N++; 
        }

        
        for (uint64_t u = 0; ; u += 2) {
            uint64_t p = (N + u) * q + 1;
            
            // 5) Выход за разрядность
            if (p >= ((uint64_t)1 << t)) break; 

            // 6) Теорема Диемитко
            // 2^(p-1) == 1 (mod p)
            // 2^(N+u) != 1 (mod p)
            if (powN(2, p - 1, p) == 1 && powN(2, N + u, p) != 1) {
                return {q, p};
            }
        }
    }
}

int main() {
    
    int t;
    vector<int> sieveEr = sieveErat();

    cout << "простые числа до 500:" <<endl;

    for (size_t i = 0; i < sieveEr.size(); ++i) {
        if (sieveEr[i]>500){
            break;
        }
        cout << sieveEr[i] << " ";
        if (i%10==0 && i!=0){
            cout << endl;
        }
    }
    cout << endl;

    cout << "разрядность ";
    cin >> t;

    
    cout << "---------------------------------------------------"<<endl;
    cout << "|     q     |     t         | Построенное число p |"<<endl;
    cout << "---------------------------------------------------"<<endl;
    for (int i = 1; i <= 10; ++i) {
        pair<int, uint64_t> result = generateGost(t, sieveEr);
        cout << "| " << setw(10) << result.first;
        cout << "| " << setw(14) << t;
        cout << "| " << setw(20) << result.second <<"|"<<endl;
    }


    cout << "--------------------------------------------------- "<<endl;

    return 0;
}