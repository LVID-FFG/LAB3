
#include "test_Pol.h"
#include "general_fun.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include <random>

using namespace std;

/*ostream& operator<< (ostream& os, vector<auto>& v){
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
}*/


tuple<unsigned long long, vector<int>, vector<int>> generate_N_3(int k, const vector<int>& control){ //k - длинна числа, control - вектор простых чисел
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> random_num(1, 90);
    unsigned long long f = 1;
    vector<int> Q = {};
    vector<int> A = {};
    int a = 0, q = 0;
    unsigned long long s = f;
    int r;
    unsigned long long n = 1;
    while(1){
        while (1){ //len_in_bit(m) < k-1
            a = random_num(gen);
            q = control[random_num(gen)];
            if (count(Q.begin(), Q.end(), q) == 0){ //считем кол-во вхождений
                s *= pow(q, a); //кандидат на множитель
                if (pow(2, k/2) <= s && s < pow(2, k/2+1)) { //если число попало в нужный диапазон
                    f = s; //возводим в степень
                    Q.push_back(q);
                    A.push_back(a);
                    break;
                }
                else{
                    if (len_in_bit(s) < k/2+1){ //если число меньше нужного
                        f = s; //возводим в степень
                        Q.push_back(q);
                        A.push_back(a);
                    }
                    else { //если число больше нужного начинаем с начала
                        s = 2;
                        f = 2;
                        Q.clear();
                        A.clear();
                        /*A.push_back(1);
                        Q.push_back(2);*/
                    };
                }    
            }
            else {
                if (size(Q) > 45){ //если простых чисел не хватает для построения начинаем с начала
                    s = f = 1;
                    Q.clear();
                    A.clear();
                    /*A.push_back(1);
                    Q.push_back(2);*/
                }
            }
        }
        random_num.param(uniform_int_distribution<>::param_type(pow(2, k/2-1), pow(2, k/2)));
        
        while(1){
            r = random_num(gen);
            if (r%2 == 0) break;
        }
        n = r*f + 1;
        if (len_in_bit(n) == k) break;
        random_num.param(uniform_int_distribution<>::param_type(1, 90));
    }
    tuple<unsigned long long, vector<int>, vector<int>> result = {n, Q, A};
    return result;
}

int test_polington(unsigned long long n, const vector<int>& Q, const vector<int>& a, int t){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> random_num(2, 50000);
    vector<int> a_list;
    for (int i = 0, c = 0; i < t;) {
        c = random_num(gen);
        if (count(a_list.begin(), a_list.end(), c) == 0){ //считем кол-во вхождений
            i++;
            a_list.push_back(c);
        }
    }
    size_t con = 0;
    for (int a : a_list){
        if (num_exp(a, n-1, n) != 1){
            return 0;
        }
        for (int q : Q){
            if(num_exp(a, (n-1)/q, n) == 1) break;
            con++;
        }
        if (con == size(Q)) return 2;
        con = 0;
    }
    return 1;
}


void polington(int k, int t, int s = 2){ //k - длина числа в битах, t - параметр надёжности теста Полингтона, s - количество раундов теста Миллера-Рабина
    vector<int> control = resheto_eratosfena();
    vector<tuple<unsigned long long, vector<int>, vector<int>>> list_of_N; //вектор чисел  N и канонических разложений N-1
    vector<unsigned long long> list_of_only_N;
    tuple<unsigned long long, vector<int>, vector<int>> N;
    for (int i = 0, test; i < 10;){      //заполняем список числами N
        N = generate_N_3(k, control);
        test = test_polington(get<0>(N), get<1>(N), get<2>(N), t);
        if (test != 0 && (count(list_of_only_N.begin(), list_of_only_N.end(), get<0>(N)) == 0) && len_in_bit(get<0>(N)) == k){
            cout << "По тесту Полингтона - ";
            test < 2 ? cout << "скорее всего простое" << endl : cout << "точно простое" << endl;
            cout << "По тесту Миллера-Рабина - ";
            cout << test_millera_rabina(get<0>(N), s) << endl;
            //cout << "размер в битах - " << len_in_bit(get<0>(N)) << endl;
            cout << get<0>(N) << endl << endl;
            list_of_N.push_back(N);
            list_of_only_N.push_back(get<0>(N));
            i++;
        }
    }
}

/*void proverka_polingt(){
    vector<tuple<unsigned long long, vector<int>, vector<int>>> test = {{13, {2}, {2}}, {29, {7}, {1}}, {61, {3, 5}, {1, 1}}, {6373, {3, 59}, {1, 1}}};
        int sost = 0;
        int  prost = 0;
        int res = 0;
        for (tuple<unsigned long long, vector<int>, vector<int>> now : test){
            for (int i = 0; i < 100; i++){
                res = test_polington(get<0>(now), get<1>(now), get<2>(now), 1);
                if (res == 0) sost++;
                if (res == 1 || res == 2) prost++;
                //else prost++;
            }
            cout << get<0>(now) << " " << fixed << setprecision(3)<< sost  << " " << prost << endl;
            sost = 0;
            prost = 0;
        }
}*/