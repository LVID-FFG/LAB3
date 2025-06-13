#include "test_gost.h"
#include "general_fun.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include <random>

using namespace std;

unsigned int generate_N_1(int t){
    uint stop = 0;
    if (t == 2) return 3;
    double q = generate_N_1(t/2);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> random_num(0.0, 1.0);
    double e;
    int N;
    int u = 0;
    unsigned int p;
    while (1){
        start:
        e = random_num(gen);
        N = ceil(pow(2, t-1)/q) + ceil(pow(2, (t-1))*e/q);
        N%2 == 1? N++: N=N;
        u = 0;
        stop++;
        if (stop > 1000000){
            return 0;
        }
        while (1){
            p = (N+u)*q+1;
            if (p > pow(2, t)) goto start;
            if(num_exp(2, p-1, p) == 1 && num_exp(2, N+u, p) != 1) return p;
            u += 2;
        }
    }
}

void gost(int k, int s = 2){ //k - длина числа в битах
    unsigned long N;
    vector<unsigned long> list_N;
    for (int i = 0, n = 0, test; i < 10;){  //заполняем список числами N
        N = generate_N_1(k);
        if (N == 0){
            cout << "Больше чисел не нашлось, генерация остановленна" << endl;
            return;
        }
        if (count(list_N.begin(), list_N.end(), N) == 0){
            list_N.push_back(N);
            cout << N << " по вероятностному тесту - " << test_millera_rabina(N, s) << endl;
            i++;
        }
    }
}
