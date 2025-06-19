#include "fun3.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include <random>
using namespace std;
 
template <typename t>
int NOD(t a, t b){
    if (a % b == 0) return b;
    if (b % a == 0) return a;
    if (a > b) return NOD(a%b, b);
    return NOD(a, b%a);
}


void fun3(int a, int b){ // n^a/b^n
    double sum = 0;
    if (b == 1) {
        cout << "infinity" << endl;
        return ;
    }
    for (int i = 0, n = 0; i < 80000; i++, n++){ //находим примерную сумму ряда 
        sum += pow(n, a)/pow(b, n);
    }

    unsigned long long sum_H = round(sum * pow(10, 9)); // строим примерную обычную дробь
    unsigned long long sum_L = pow(10, 9);
    if (sum_H % 10 == 0){ // если последний знак 0
        int nod = NOD(sum_H, sum_L);
        sum_H /= nod;
        sum_L /= nod;
        if ((sum_L % 2 == 0 || sum_L % 5 == 0 || sum_L == 1) && sum_L < 10000000){ // если это рациональное число
            cout  << sum_H << "/" << sum_L << endl;
            return;
        }
        
    }

    int nod = NOD(sum_H, sum_L);
    sum_H /= nod;
    sum_L /= nod;
    if ((sum_H/10)%10 == 0 && b == 2){ //для чисел вида ***********.00000000000001244 где числитель *************03
        cout << static_cast<int>(sum) << endl;
        return;
    }

    for (int i = 1; i <= 30; i++){// для чисел с знаменателем 2 большой степени
        if ((static_cast<unsigned long>(round(sum*pow(2, i))*10000) - static_cast<unsigned long>(round(sum*pow(2, i)*10000))) == 0){
            cout << static_cast<unsigned long>(sum*pow(2, i))<< "/" << static_cast<unsigned long>(pow(2, i)) << endl;
            return;
        }
    }
    for (int i = 1; i <= 10; i++){ // для чисел с знаменателем 5 большой степени
        if ((static_cast<unsigned long>(round(sum*pow(5, i))*10000) - static_cast<unsigned long>(round(sum*pow(5, i)*10000))) == 0){
            cout << static_cast<unsigned long>(sum*pow(5, i))<< "/" << static_cast<unsigned long>(pow(5, i)) << endl;
            return;
        }
    }
    cout << "irrational" << endl;
    return;

}