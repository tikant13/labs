#include <iostream> 

using namespace std;

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

int main(){
    cout << mod (5, 2026, 6)<< endl;
    return 0;
    
}