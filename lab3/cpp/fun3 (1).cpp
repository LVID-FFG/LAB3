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
    if ((b-1)%5 != 0 && (b-1)%2 != 0 && b-1 != 1 || b-1 == 6){
        cout << "irrational" << endl;
        return ;
    }
    unsigned long long num_h, num_l;
    switch (a){
        case 1:
            num_h = b;
            num_l = pow((b-1), 2);
            break;
        case 2:
            num_h = b*(b+1);
            num_l = pow((b-1), 3);
            break;
        case 3:
            num_h = b*(pow(b, 2)+4*b+1);
            num_l = pow((b-1), 4);
            break;
        case 4:
            num_h = b*(pow(b, 3) +11*pow(b, 2)+11*b+1);
            num_l = pow((b-1), 5);
            break;
        case 5:
            num_h = b*(pow(b, 4) +26*pow(b, 3)+66*pow(b, 2)+26*b+1);
            num_l = pow((b-1), 6);
            break;
        case 6:
            num_h = b*(pow(b, 5) +57*pow(b, 4)+302*pow(b, 3)+302*pow(b, 2)+57*b+1);
            num_l = pow((b-1), 7);
            break;
        case 7:
            num_h = b*(pow(b, 6) + 120*pow(b, 5) + 1191*pow(b, 4) + 2416*pow(b, 3) + 1191*pow(b, 2) + 120*b + 1);
            num_l = pow((b-1), 8);
            break;
        case 8:
            num_h = b*(pow(b, 7) + 247*pow(b, 6) + 4293*pow(b, 5) + 15619*pow(b, 4) + 15619*pow(b, 3) + 4293*pow(b, 2) + 247*b + 1);
            num_l = pow((b-1), 9);
            break;
        case 9:
            num_h = b*(pow(b, 8) + 502*pow(b, 7) + 14608*pow(b, 6) + 88234*pow(b, 5) + 156190*pow(b, 4) + 88234*pow(b, 3) + 14608*pow(b, 2) + 502*b + 1);
            num_l = pow((b-1), 10);
            break;
        case 10:
            num_h = b*(pow(b, 9) + 1013*pow(b, 8) + 47840*pow(b, 7) + 455192*pow(b, 6) + 1310354*pow(b, 5) + 1310354*pow(b, 4) + 455192*pow(b, 3) + 47840*pow(b, 2) + 1013*b + 1);
            num_l = pow((b-1), 11);
            break;
        default:
            break;
       }
    unsigned long long nod = NOD(num_h, num_l);
    cout << num_h/nod << "/" << num_l/nod << endl;
}