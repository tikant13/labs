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
    int ya;
    int yb;
    int zab;
    int zba;
    // открытая информация
    int p = 23; 
    int g = 5;
    // закрытая информация 
    int xa = 7;
    int xb = 4;

    ya = mod(g, xa, p);
    yb = mod(g, xb, p);

    zab = mod (yb, xa, p);
    zba = mod (ya, xb, p);

    cout << zab << " "<< zba<<endl;


    return 0;
    
}