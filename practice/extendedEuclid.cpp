#include <iostream>

using namespace std;


int NOD(int a, int b, int &u, int &v) {
    
    u = 1; 
    v = 0;
    int uPrev = 0; 
    int vPrev = 1;
    
    int tempA = a;
    int tempB = b;

    while (tempB != 0) {
       
        int wholePart = tempA / tempB;  // находим целую часть от деления

        
        int remainder = tempA % tempB; // находим остаток
        tempA = tempB;
        tempB = remainder;

        // новые u и v
        // новое значение = старое - частное * текущее
        int nextu = u - wholePart * uPrev;
        u = uPrev;
        uPrev = nextu;

        int nextv = v - wholePart * vPrev;
        v = vPrev;
        vPrev = nextv;
    }

    return tempA; // НОД
}

int main() {
    int a, b;
    int u, v;

    cout << "Введите два числа через пробел: ";
    cin >> a >> b;

    int resultNOD = NOD(a, b, u, v);

    
    cout << "НОД(" << a << ", " << b << ") = " << resultNOD << endl;
    cout << "(u, v) = " << u << ", " << v << endl;
    cout <<  a << "*" << u << " + " << b << "*" << v << " = " << (a * u + b * v) << endl;

    return 0;
}