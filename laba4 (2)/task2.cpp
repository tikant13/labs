#include <iostream>
#include<random>
#include<vector>
#include<algorithm>

using namespace std;

void genVec(const int& n, vector<int>& originVec){ 
    random_device rd;
    mt19937 gener(rd());
    uniform_int_distribution<> distr(-100, 100);
    for (int i=0; i<n; ++i){
        originVec.push_back(distr(gener));
    }
    
}

pair<int, int> minMax(vector<int>& vect) { // находим минимальный и максимальное значение и их индексы
    int min = 0, max = 0;
    for (int i = 1; i < vect.size(); ++i) {
        if (vect[i] < vect[min]) {
            min = i;
        }
        if (vect[i] > vect[max]) {
            max = i;
        }
    }
    return {min, max};
}

double arifNegative(const vector<int>& vect) { // находим среднее арифметическое для отрицательных 
    double sum = 0;
    int c = 0;
    for (int val : vect) {
        if (val < 0) {
            sum += val;
            c++;
        }
    }
    if (c > 0) {
        return sum / c;
    }
    return 0;
}

double arifPositive(const vector<int>& vect) { // находим среднее арифметическое для положительных
    double sum = 0;
    int c = 0;
    for (int val : vect) {
        if (val > 0) {
            sum += val;
            c++;
        }
    }
    if (c > 0) {
        return sum / c;
    }
    return 0;
}

vector<int> longestSequence(const vector<int>& vect) { //самая длинная убывающая последовательность
    
    vector<int> longestSeq; //самая длинная 
    vector<int> currentSeq; //текущая
    currentSeq.push_back(vect[0]);
    
    for (size_t i = 1; i < vect.size(); ++i) {
        if (vect[i] < vect[i - 1]) {
            currentSeq.push_back(vect[i]);
        } else {
            if (currentSeq.size() > longestSeq.size()) {
                longestSeq = currentSeq;
            }
            currentSeq.clear();
            currentSeq.push_back(vect[i]);
        }
    }
    
    if (currentSeq.size() > longestSeq.size()) { // проверяем последнюю последовательность
        longestSeq = currentSeq;
    }
    
    return longestSeq;
}

bool isPrime(int num) { // проверяем простое ли число
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

vector<int> isPrimeLess(const vector<int>& vect, double limit) { //ищем числа меньше заданного
    vector<int> result;
    
    for (int val : vect) {
        if (val > 0 && val < limit && isPrime(val)) {
            if (find(result.begin(), result.end(), val) == result.end()) { // проверяем, не добавили ли мы уже это число
                result.push_back(val);
            }
        }
    }
    return result;
}

void matrix(const int& N) {
    int firstElement = 30;  // первый элемент первой строки
    
    for (int i = 0; i < N; ++i) {
        
        int curFirst = firstElement; // Вычисляем первый элемент текущей строки
        
        
        for (int j = 0; j < i; ++j) {
            if ((j + 1) % 2 == 1) {  
                curFirst += 5;
            } else {                   
                curFirst += 10;
            }
        }
        
       
        for (int j = 0; j < 4; ++j) {
            cout << curFirst + j * 10 << " ";
        }
        cout << endl;
    }
}

int main(){
    int n;
    cin >> n;

    if (n<10){
        cout << "Размер массива должен быть больше 10"<<endl;
        return 0;
    }
    vector<int> originVec;
    genVec(n, originVec);

    cout << "Задание 1"<<endl;
    for (int i =  0;i < originVec.size(); ++i  ){ // 1 задание
        cout << originVec[i] << " ";
        if ((i+1)%10==0 ){ // перенос строки каждые 10 элементов чтобы не было длинной строки 
            cout << endl;
        }
    }

    cout << endl << "Задание 2" << endl;
    double arifNeg = arifNegative(originVec);
    double arifPos = arifPositive(originVec);
    cout << "Среднее арифметическое отрицательных элементов: " << arifNeg << endl;
    cout << "Среднее арифметическое положительных элементов: " << arifPos << endl;

    pair <int, int> mima = minMax(originVec); // находи индекс у минимального и максимального значения
    cout << "Индекс минимального элемента: " << mima.first << " значение: " << originVec[mima.first]<< endl;
    cout << "Индекс максимального элемента: " << mima.second << " значение: " << originVec[mima.second]<< endl;

    swap(originVec[mima.first], originVec[mima.second]); // меняем местами min и max
    
    cout << "Модифицированный массив, где min и max поменяны местами" << endl;
    for (int i = 0; i < originVec.size(); ++i) {
        cout << originVec[i] << " ";
        if ((i + 1) % 10 == 0) cout << endl;
    }

    cout<<endl<<"Задание 3"<<endl;
    vector<int> decrVector = longestSequence(originVec);
    cout << "Длинна последовательности "<<decrVector.size()<<endl;
    cout <<"Сама последовательность ";
    for (int i : decrVector) {
        cout << i << " ";
    }
    cout << endl;

    cout<<"Задание 4"<<endl;
    vector<int> primes = isPrimeLess(originVec, arifPos);
    
    if (primes.empty()) { 
        cout << "Простых чисел, удовлетворяющих условию, не найдено." << endl;
    } else {
        cout << "Найденные простые числа: ";
        for (int i : primes) {
            cout << i << " ";
        }
        cout << endl;
    }

    cout << "Задание 5"<<endl<<"Введите N"<<endl;
    int N;
    cin >> N;
    matrix(N);


    cout << endl;
    return 0;
}