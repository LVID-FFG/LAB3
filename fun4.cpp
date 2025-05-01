#include "fun4.h"

#include <iostream>
#include <vector>
using namespace std;
pair<int, int> strat_max_score(int s, int m, vector<int>& posl){
    int best_m = 0;
    int our_res = 0;
    int our_res_best = -999999;
    for (int j = 1; j <= m; j++){
        our_res = 0;
        for (int i = 0; i < j && s+i < size(posl); i++){
            our_res += posl[s + i];
        }
        if (our_res > our_res_best){
            our_res_best = our_res;
            best_m = j;
        }
        
    }
    if (best_m == 0) best_m++;
    pair<int, int> result = {best_m, our_res_best};
    return result;
}

pair<int, int> strat_best_score(int s, int m, vector<int>& posl){ //находит наилучшую разницу между получением очков себе и не получением их противником
    int best_m = 0;
    int our_res = 0;
    int our_res_best = -999999;
    int difference = -999999;
    pair<int, int> enemy;
    for (int j = 1; j <= m; j++){
        our_res = 0;
        for (int i = 0; i < j && s+i < size(posl); i++){
            our_res += posl[s + i];
        }
        enemy = strat_max_score(s+j, m , posl);
        if (our_res - enemy.second > difference){
            difference = our_res - enemy.second;
            our_res_best = our_res;
            best_m = j;
        }
        
    }
    if (best_m == 0) best_m++;
    pair<int, int> result = {best_m, our_res_best};
    return result;
}


void fun4(int m){ // m - максимальная длинна хода
    vector<int> posl;
    int s = 0; // сколько чисел зачеркнули
    int i = 0;
    cout << "Введите последовательность чисел через пробел, для завершенния ввода введите любую букву и enter" << endl;
    while(cin >> i){
        posl.push_back(i);
    }
    int pavel_score = 0;
    int vika_score = 0;
    int turn = 0; // 0 - Pavel, 1 - Vika текущий ход
    pair<int, int> score;
    while (s < size(posl)){
        //cout << "Turn = " << turn << " ------------------" << endl;
        if (turn % 2 == 0){
            pair<int, int> score = strat_best_score(s, m, posl);
            pavel_score += score.second;
            s += score.first;
        }
        else{
            pair<int, int> score = strat_best_score(s, m, posl);
            vika_score += score.second;
            s += score.first;
        }
        //cout << s << " "  << pavel_score << " / " << vika_score << endl;
        turn++;
    }
    if (pavel_score > vika_score) {
        cout << "1" << endl; //"PAVEL WIN"
        //cout << pavel_score << " / " << vika_score << endl;
        return;
    }
    else {
        cout << "0" << endl; //"VIKA WIN"
        //cout << pavel_score << " / " << vika_score << endl;
        //return;
    }
    return;
}