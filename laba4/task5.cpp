#include<iostream>
#include<vector>
#include<random>

using namespace std;

//добряк (первые 10 раундов доверяет)
bool altruist( const int& roundNumber, vector<bool>& selfChoices, vector<bool>& enemyChoices ){

    int betrayal = 0; //предательство

    if (roundNumber>=10){
        for (int i = roundNumber-10; i<roundNumber; ++i ){ //смотрим преладельства и сотруд
            if (enemyChoices[i] == false){
                ++betrayal;
        }
        if (betrayal>6){
            return false;
        }
    }
    }

    return true;

}

// может обмануть иногда, если обмануть несколько раз обмануть, то тоже обманывает
bool careful(const int& roundNumber, vector<bool>& selfChoices, vector<bool>& enemyChoices){
    
    int betrayal = 0; //предательство
    int chance; // шанс на  предател

    mt19937 gen(random_device{}());
    chance = gen()%100;

    if(roundNumber>=10){
        for (int i = roundNumber-10; i<roundNumber; ++i ){ //смотрим преладельства и сотрудничества 
            if (enemyChoices[i] == false){
                ++betrayal;
            }
        }
        if (chance>(85-betrayal)){ // с шансом предаём
            return false;
        }

        // если предали больше 5 раз
        if (betrayal>=5 ){ 
            return false;
        }

    } else {
        if (roundNumber!=1){
            return enemyChoices.back(); //отвечаем тем же до 10 раунда
        }
    }

    
    return true;

}
 
// часто идёт на обман, будет пытаться узнать какой алгоритм перед ним. C другим злым будет стараться сотрудничать, чятобы набрать болше очков
bool evil(const int& roundNumber, vector<bool>& selfChoices, vector<bool>& enemyChoices){

    int betrayal = 0; //предательство
    int chance; // шанс на  предател
    int strat; // стратегия противника

    mt19937 gen(random_device{}());
    chance = gen()%100;

    if (roundNumber==1){ // вначале всегда обманывает
        return false;
    } else { // если не первый ход, то смотрит кто перед нами
        if (enemyChoices[0]==false){
            strat = 3; // перед нами злодей
        }
    }

    // если перед нами тоже злодей, то сотрудничаем, но иногда можно и предать
    if (strat == 3){ 
        if (chance > 95){ 
            return false;
        }
        return true;
    } 

    if (strat!=3 && roundNumber==2){ //ещё раз обманываем, если это не злодей, чтобы проверить кто перед нами
        return false;
    } else {
        if (enemyChoices[1]==true){
            if (enemyChoices.back()==true){ // если это добряк, то обманываем, поека не перестнет доверять
                return false;
            } 
            return true;
            
        } else { // если это осторожный, то пытаемся уйти в одинаковое кол-во очков
            if (roundNumber==3){  // пытаемся востановить отношение
                return true; 
            }
            return enemyChoices.back(); // отвечаем зеркально
            
        }
    }

    
    
}



pair<int, int> launch(int strategy1, int strategy2, int &rounds){ // вызов наших алгоритмов
    bool action1;
    bool action2;
    int score1 = 0;
    int score2 = 0;
    vector<bool> selfChoices1;
    vector<bool> selfChoices2;

    for (int round = 1; round<=rounds; ++round){
        if (strategy1 == 1){ //первый игрок
            action1 = altruist (round, selfChoices1, selfChoices2);
        } else if (strategy1 == 2) {
            action1 = careful (round, selfChoices1, selfChoices2);
        } else {
            action1 = evil (round, selfChoices1, selfChoices2);
        }

        if (strategy2 == 1){ //второй игрок
            action2 = altruist (round, selfChoices2, selfChoices1);
        } else if (strategy2 == 2) {
            action2 = careful (round, selfChoices2, selfChoices1);
        } else {
            action2 = evil (round, selfChoices2, selfChoices1);
        }

        // добавляем последнее решение
        selfChoices1.push_back(action1);
        selfChoices2.push_back(action2);

        if (action1 == true && action2 == true){ 
            score1+=24;
            score2+=24;
        } else if (action1>action2){
            score2+=20;
        } else if (action1<action2) {
            score1+=20;
        } else {
            score1+=4;
            score2+=4;
        }

        cout << selfChoices1.back() << "    " << selfChoices2.back()<<"    очки 1: "<<score1<< " очки 2: "<<score2<<endl;


    }
    return {score1, score2};

}

int main(){
    mt19937 gent(random_device{}());
    int rounds = 100 + gent() % 101;

    int strategy1;
    int strategy2;
    int totalAltruist = 0;
    int totalCareful = 0;
    int totalEvil = 0;


    cout << "Три стратегии:"<<endl;
    cout <<"1) Добряк"<<endl;
    cout <<"2) Сомнительная личность ()"<<endl;
    cout <<"3) Злодей"<<endl;


    cout << "Количество раундов: " << rounds << endl << endl;

    // Добряк vs Сомнительный
    pair<int, int> res1 = launch(1, 2, rounds);
    totalAltruist += res1.first;
    totalCareful += res1.second;
    cout << "Матч 1: Добряк (" << res1.first << ") vs Сомнительный (" << res1.second << ")" << endl<< endl;

    // Сомнительный vs Злодей
    pair<int, int> res2 = launch(2, 3, rounds);
    totalCareful += res2.first;
    totalEvil += res2.second;
    cout << "Матч 2: Сомнительный (" << res2.first << ") vs Злодей (" << res2.second << ")" << endl<<endl;

    //Злодей vs Добряк
    pair<int, int> res3 = launch(3, 1, rounds);
    totalEvil += res3.first;
    totalAltruist += res3.second;
    cout << "Матч 3: Злодей (" << res3.first << ") vs Добряк (" << res3.second << ")" << endl<< endl;

    cout <<endl<< "Итоговый счёт" << endl;
    cout << "1. Добряк: " << totalAltruist << " очков" << endl;
    cout << "2. Сомнительный: " << totalCareful << " очков" << endl;
    cout << "3. Злодей: " << totalEvil << " очков" << endl;

    // Определение победителя
    if (totalAltruist >= totalCareful && totalAltruist >= totalEvil)
        cout << endl<< "Победил Добряк" << endl;
    else if (totalCareful >= totalAltruist && totalCareful >= totalEvil)
        cout <<endl<< "Победила Сомнительная личность" << endl;
    else
        cout <<endl<< "Победил Злодей" << endl;

    return 0;
}