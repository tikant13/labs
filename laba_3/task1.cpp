#include <iostream>
#include <iomanip> 
#include <string> 
#include <math.h>

using namespace std;

void printFun(double x, double y){
    cout<< "|" << setw(11) << x << "|" <<setw(11) << fixed << setprecision(4)<< y <<"|"<<endl;
    cout<<"-------------------------"<< endl;
}

int main(){

    double x;
    double step;
    double xk;
    double y;

    cout << "Введите x начальное и x конечное" << endl;
    cin >> x >> xk;
    cout << "Введите шаг"<<endl;
    cin >> step;

    cout<<"-------------------------" << endl;
    cout<<"|     x     |     y     |" << endl;
    cout<<"-------------------------" << endl;

    while (x<=xk){

        if (x>=-9 && x<=-5){ //полуокружность
            y = 2 - sqrt(4 - pow((x+7),2));
        }
        else if (x>-5 && x<=-4){ //линия горизонтальная
            y = 2;
        }
        else if (x>-4 && x<=0) {//наклонная
            y = -0.5 * x;
        } 
        else if (x>0 && x<3){ // порабола 
            y = -0.5 * x * (x - 3);
        }
        else if (x>=3){ // наклонная
            y = x - 3;
        }
        if (x>=-9){
            printFun(x, y);
        }
        x +=step;
    }
    
    return 0;
} 