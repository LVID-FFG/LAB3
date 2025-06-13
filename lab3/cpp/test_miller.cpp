
#include "test_miller.h"
#include "general_fun.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include <random>
using namespace std;

ostream& operator<< (ostream& os, vector<auto>& v){
    for(auto i : v){
        os << i << " ";
    }
    return os;
}
ostream& operator<< (ostream& os, tuple<unsigned long long, vector<int>, vector<int>>& t){
    os << get<0>(t) << endl;
    os << get<1>(t) << endl;
    os << get<2>(t) << endl;
    return os;
}
ostream& operator<< (ostream& os, vector<tuple<unsigned long long, vector<int>, vector<int>>>& v){
    for(auto i : v){
        os << i;
    }
    return os;
}


tuple<unsigned long long, vector<int>, vector<int>> generate_N_2(int k, const vector<int>& control){ //k - размер в битах, control - вектор простых чисел
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> random_num(1, 50);
    unsigned long long m = 2;
    vector<int> Q = {2};
    vector<int> A = {1};
    int a = 0, q = 0;
    unsigned long long s = m;
    while (1){ //len_in_bit(m) < k-1
        a = random_num(gen);
        q = control[random_num(gen)];
        if (count(Q.begin(), Q.end(), q) == 0){ //считем кол-во вхождений
            s *= pow(q, a); //кандидат на множитель
            if (pow(2, k-1) <= s && s < pow(2, k)) { //если число попало в нужный диапазон
                m = s; //возводим в степень
                Q.push_back(q);
                A.push_back(a);
                break;
            }
            else{
                if (len_in_bit(s) < k){ //если число меньше нужного
                    m = s; //возводим в степень
                    Q.push_back(q);
                    A.push_back(a);
                }
                else { //если число больше нужного начинаем с начала
                    s = 2;
                    m = 2;
                    Q.clear();
                    A.clear();
                    A.push_back(1);
                    Q.push_back(2);
                };
            }    
        }
        else {
            if (size(Q) > 45){ //если простых чисел не хватает для построения начинаем с начала
                s = m = 2;
                Q.clear();
                A.clear();
                A.push_back(1);
                Q.push_back(2);
            }
        }
    }
    unsigned long long n = m + 1;
    tuple<unsigned long long, vector<int>, vector<int>> result = {n, Q, A};
    return result;
}

int test_millera(tuple<unsigned long long, vector<int>, vector<int>>& num, int t){ // 0 - составное, 1 - вероятно составное, 2 - простое
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> random_num(1, 100);
    vector<int> t_list;
    for (int i = 0, c = 0; i < t;) {
        c = random_num(gen);
        if (count(t_list.begin(), t_list.end(), c) == 0){ //считем кол-во вхождений
            i++;
            t_list.push_back(c);
        }
    }

    for (int i : t_list){
        if(num_exp(i, get<0>(num)-1, get<0>(num)) != 1){
            return 0;
        }
    }

    vector<int> q_list = get<1>(num);
    int c = 0; // счётчик успехов
    for (int q : q_list){
        for (int i : t_list){
            if (num_exp(i, (get<0>(num)-1)/q, get<0>(num)) == 1) {
                c++;
            }
            else {
                break;
            }
        }
        if (c == size(t_list)){
            return 1;
        }
        c = 0; 
    }
    return 2;
}

void miller(int k, int t, int s){ //k - длина числа в битах, t - параметр надёжности теста Миллера, s - количество раундов теста Миллера-Рабина
    vector<int> control = resheto_eratosfena();
    cout << "Решето Эратосфена:" << endl;
    cout << control << endl;
    vector<tuple<unsigned long long, vector<int>, vector<int>>> list_of_N; //вектор чисел  N и канонических разложений N-1
    vector<unsigned long long> list_of_only_N;
    tuple<unsigned long long, vector<int>, vector<int>> N;
    unsigned long iter = 0;
    int K = 0;
    for (int i = 0, n = 0, test; i < 10;){      //заполняем список числами N
        if (iter > 5000) {
            cout << "Больше простых чисел не нашлось" << endl;
            return;
        }
        iter++;
        N = generate_N_2(k, control);
        test = test_millera(N, t);
        if (test != 2 &&  test_millera_rabina(get<0>(N), s) == "вероятно простое") K++;
        if (test != 0 && (count(list_of_only_N.begin(), list_of_only_N.end(), get<0>(N)) == 0)){
            cout << "По тесту Миллера - ";
            test < 2 ? cout << "скорее всего простое" << endl : cout << "точно простое" << endl;
            cout << "По тесту Миллера-Рабина - ";
            cout << test_millera_rabina(get<0>(N), s) << endl;
            cout << "k = " << K << endl;
            K = 0;
            cout << get<0>(N) << endl;
            list_of_N.push_back(N);
            list_of_only_N.push_back(get<0>(N));
            i++;
        }
    }
}