//g++ -w fun1.cpp fun3.cpp fun4.cpp fun5.cpp general_fun.cpp test_gost.cpp test_Pol.cpp test_miller.cpp lab3_main.cpp; ./a.out; rm a.out
#include "fun1.h"
#include "test_miller.h"
#include "test_Pol.h"
#include "test_gost.h"
#include "fun3.h"
#include "fun4.h"
#include "fun5.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include <random>
using namespace std;


int main(){
    int x = 0;
    //F1
    double x_n = 0, x_k = 0, stp = 0;
    //F2
    int choice, bit, t, s;
    //F3
    int a, b;
    //F4
    int m;
    //F5
    double T, T_s, r;
    int t_max, t_st;
    while (1){
        cout << "Выберете задание,  для выхода введите 0" << endl << "График - 1"<< endl << "Генераторы простых чисел - 2"<< endl << "Ряд - 3"<< endl << "Игра - 4" << endl <<"Кофе - 5" << endl;
        x = 0;
        cin >> x;
        switch (x){
            case 1:
                cout << "Введите начало отрезка" << endl;
                cin >> x_n;
                if (cin.fail()){
                    cout << "Ошибка ввода" << endl;
                    exit(0);
                }
                cout << "Введите конец отрезка" << endl;
                cin >> x_k;
                if (cin.fail() || x_k < x_n){
                    cout << "Ошибка ввода" << endl;
                    exit(0);
                }
                cout << "Введите шаг" << endl;
                cin >> stp;
                if (cin.fail() || stp <= 0){
                    cout << "Ошибка ввода" << endl;
                    exit(0);
                }
                fun1(x_n, x_k, stp);
                break;
            case 2:
                cout << "Выберете генератор простых чисел \n1 - Миллера, 2 - Полингтона, 3 - ГОСТ" << endl;
                cin >> choice;
                if (cin.fail() ||choice < 1 || choice > 3){
                    cout << "Ошибка ввода" << endl;
                    exit(0);
                }
                switch (choice){
                    case 1:
                        cout << "Введите размер числа в битах (не более 32)" << endl;
                        cin >> bit;
                        if (cin.fail() || bit <= 0 || bit > 32){
                            cout << "Ошибка ввода" << endl;
                            exit(0);
                        }
                        cout << "Введите параметр надёжности теста Миллера" << endl;
                        cin >> t;
                        if (cin.fail() || t <= 0){
                            cout << "Ошибка ввода" << endl;
                            exit(0);
                        }
                        cout << "Введите количество раундов теста Миллера-Рабина" << endl;
                        cin >> s;
                        if (cin.fail() || s <= 0){
                            cout << "Ошибка ввода" << endl;
                            exit(0);
                        }
                        miller(bit, t, s);
                        break;
                    case 2:
                        cout << "Введите размер числа в битах (не более 32)" << endl;
                        cin >> bit;
                        if (cin.fail() || bit <= 0 || bit > 32){
                            cout << "Ошибка ввода" << endl;
                            exit(0);
                        }
                        cout << "Введите параметр надёжности теста Полингтона" << endl;
                        cin >> t;
                        if (cin.fail() || t <= 0){
                            cout << "Ошибка ввода" << endl;
                            exit(0);
                        }
                        cout << "Введите количество раундов теста Миллера-Рабина" << endl;
                        cin >> s;
                        if (cin.fail() || s <= 0){
                            cout << "Ошибка ввода" << endl;
                            exit(0);
                        }
                        polington(bit, t, s);
                        break;
                    case 3:
                        cout << "Введите размер числа в битах не более 32" << endl;
                        cin >> bit;
                        if (cin.fail() || (bit > 32)){
                            cout << "Ошибка ввода" << endl;
                            exit(0);
                        }
                        cout << "Введите количество раундов теста Миллера-Рабина" << endl;
                        cin >> s;
                        if (cin.fail() || s <= 0){
                            cout << "Ошибка ввода" << endl;
                            exit(0);
                        }
                        gost(bit, s);
                        break;
                    default:
                        break;
                }
                break;
            case 3:
                cout << "Введите a, (n^a/b^n)" << endl;
                cin >> a;
                if (cin.fail() || a < 1 || a > 10){
                    cout << "Ошибка ввода" << endl;
                    exit(0);
                }
                cout << "Введите b" << endl;
                cin >> b;
                if (cin.fail() || b < 1 || b > 10){
                    cout << "Ошибка ввода" << endl;
                    exit(0);
                }
                fun3(a, b);
                break;

            case 4:
                cout << "Введите максимальную длинну хода (от 4 до 100)" << endl;
                cin >> m;
                if (cin.fail() || m < 4 || m > 100){
                    cout << "Ошибка ввода" << endl;
                    exit(0);
                }
                fun4(m);
                exit(0);

            case 5:
                cout << "Введите начальную температуру кофе" << endl;
                cin >> T;
                if (cin.fail()){
                    cout << "Ошибка ввода" << endl;
                    exit(0);
                }
                cout << "Введите температуру окружающей среды" << endl;
                cin >> T_s;
                if (cin.fail() || T_s > T){
                    cout << "Ошибка ввода" << endl;
                    exit(0);
                }
                cout << "Введите коэффициент остывания" << endl;
                cin >> r;
                if (cin.fail() || r <= 0 || r >= 1){
                    cout << "Ошибка ввода" << endl;
                    exit(0);
                }
                cout << "Введите время наблюдения" << endl;
                cin >> t_max;
                if (cin.fail() || t_max <= 0){
                    cout << "Ошибка ввода" << endl;
                    exit(0);
                }
                cout << "Введите шаг измерения температуры" << endl;
                cin >> t_st;
                if (cin.fail() || t_st <= 0){
                    cout << "Ошибка ввода" << endl;
                    exit(0);
                }
                fun5(T, T_s, r, t_max, t_st);
                break;
            default:
                cout << "Завершение работы" << endl;
                exit(0);
        }
        cout << endl;
    }
    //fun1(-10, 15, 1); //x начала, х конца, шаг
    //fun2(16, 3, 3); //k - длина числа в битах, t - параметр надёжности теста Миллера, s - количество раундов теста Миллера-Рабина
    //fun3(5, 6); // n^a/b^n
    //fun4(3); // m - максимальная длинна хода
    //fun5(500.0, 25.0, 0.1, 20, 1); //температура кофе, окр. температура, коэф. остывания, макс. время, шаг измерения времени. 
}