#include "fun1.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;

void fun1(double x, double x_con, double step){ //x начала, х конца, шаг
    vector<double> result;
    double y = 0;
    double s = x;
    cout << fixed << setprecision(2);
    for(;x <= x_con; x += step){
        if (x < -10){
            y = 2;
        }
        if (-10 <= x && x <= -6){
            y = -1*sqrt(4 - (x+8)*(x+8))+2;
        }
        if (-6 < x && x <= -4){
            y = 2;
        }
        if (-4 < x && x <= 2){
            y = -1*(x/2);
        }
        if (2 < x){
            y = x-3;
        }
        result.push_back(y);
    }
    cout <<  "x y" << endl;
    for (double i : result){
        cout << s << " " << i << endl;
        s += step;
    }
}