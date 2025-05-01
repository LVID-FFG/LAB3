#include "fun5.h"

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void fun5(double T, double T_s, double r, int t_max, int t_step){ //температура кофе, окр. температура, коэф. остывания, макс. время, шаг измерения времени.  
    cout << "Время Температура кофе" << endl;
    vector<pair<int, double>> temp_cofe = {{0, T}};
    pair<int, double> temp_cofe_now;
    double dT = 0;
    for(int i = 1; i <= t_max; i += 1){
        dT = -1*r*(T - T_s); //вычисляем dT/dt
        T += dT;
        temp_cofe_now = {i, T};
        temp_cofe.push_back(temp_cofe_now);
        //cout << setw(5) << fixed << setprecision(1) << i << " " << T << endl;
    }
    for (pair<int, double> temp_cofe_now : temp_cofe){
        if (temp_cofe_now.first%t_step == 0){
            cout << setw(5) << fixed << setprecision(1) << temp_cofe_now.first << " " << temp_cofe_now.second << endl;
        }
    }
}