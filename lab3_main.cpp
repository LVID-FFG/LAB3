#include "fun1.h"
#include "fun2.h"
#include "fun3.h"
#include "fun4.h"
#include "fun5.h"

#include <windows.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include <random>
using namespace std;



int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "russian");
    int x = 0;
    //F1
    double x_n = 0, x_k = 0, stp = 0;
    //F2
    int bit, t, s;
    //F3
    int a, b;
    //F4
    int m;
    //F5
    double T, T_s, r;
    int t_max, t_st;
    while (1){
        cout << "Выберете задание,  для выхода введите 0" << endl << "График - 1"<< endl << "Генератор простых чисел - 2"<< endl << "Ряд - 3"<< endl << "Игра - 4" << endl <<"Кофе - 5" << endl;
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
                cout << "Введите длину числа в битах (от 8 до 32)" << endl;
                cin >> bit;
                if (cin.fail() || bit < 8 || bit > 32){
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
                fun2(bit, t, s);
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
                exit(0);
        }

    }
    //fun1(-10, 15, 1); //x начала, х конца, шаг
    //fun2(16, 3, 3); //k - длина числа в битах, t - параметр надёжности теста Миллера, s - количество раундов теста Миллера-Рабина
    //fun3(5, 6); // n^a/b^n
    //fun4(3); // m - максимальная длинна хода
    //fun5(500.0, 25.0, 0.1, 20, 1); //температура кофе, окр. температура, коэф. остывания, макс. время, шаг измерения времени. 
}