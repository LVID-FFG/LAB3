#include "fun2.h"

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

int len_in_bit(auto a){
    int result = 0;
    while (a != 0){
        result++;
        a /= 2;
    }
    return result;
}

vector<int> resheto_eratosfena(){
    vector<int> result = {1};
    int n = 500;
    for (int i = 2; i < 500; i++){ //заполняем вектор числами от 1 до 499
        result.push_back(i);
    }
    for (int i = 0, x = 2; x < 500; x++, i++){
        for(size_t j = i; j < size(result); j++){
            if(result[j] % x == 0 && result[j] != x){
                result[j] = 0;
            }
        }
    }
    result.erase(remove(result.begin(), result.end(), 0), result.end());
    //remove(result.begin(), result.end(), 0) - перемещаем 0 в конец вектора, результат итератор указывающий на 1-й 0.
    //erase(remove(result.begin(), result.end(), 0), result.end()) (удаляет 0 из конца вектора)
    return result;
}

tuple<unsigned long long, vector<int>, vector<int>> generate_N(int k, const vector<int>& control){ //k - кол-во множителей, control - вектор простых чисел
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
            s *= pow(q, a);
            if (pow(2, k-1) <= s && s <= pow(2, k)) {
                m = s; //возводим в степень
                Q.push_back(q);
                A.push_back(a);
                break;
            }
            else{
                if (len_in_bit(s) < k){
                    m = s; //возводим в степень
                    Q.push_back(q);
                    A.push_back(a);
                }
                else {
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
            if (size(Q) > 45){
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

unsigned long num_exp(auto n, auto exp, auto p){
    if (exp == 0) return 1;
    unsigned long z = num_exp(n % p, exp / 2, p) % p;
    if (exp % 2 == 0)
        return (z * z) % p;
    else
        return ((n % p) * ((z * z) % p)) % p;
}

string test_millera_rabina(unsigned long long n, int k){ //n - число на проверку, k - число раундов, вероятность ошибки = 4^(-k)  (k = 2, вероятность = 0.0625)
    int s = 0;
    unsigned long long t = n - 1;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> random_num(2, 10000000);
    for (;t%2 == 0;){ //ищем  s такое что 2^(s)*t = n
        s++;
        t /= 2;
    }
    unsigned long long x = 0;
    for (int i = 0; i < k; i++){
        x = num_exp(random_num(gen), t, n);
        //cout << "!!!!!!!!!!"<<x << endl;
        if (x == 1 || x == n-1) continue;
        for(int j=0; j < s-1; j++){
            x = num_exp(x, 2, n);
            //cout << x << endl;
            if (x == 1) return "составное";
            if (x == n-1) continue;
        }
        return "составное";
    }
    return "вероятно простое";
}

int test_millera(tuple<unsigned long long, vector<int>, vector<int>>& num, int t){ // 0 - составное, 1 - вероятно простое, 2 - простое
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
            //num_exp(pow(i, (get<0>(num)-1), get<0>(num)))
            if (num_exp(i, (get<0>(num)-1)/q, get<0>(num)) == 1) {
                c++;
            }
            else {
                break;
            }
        }
    }
    if (c < size(q_list)){
        return 1;
    } 
    else {
        return 2;
    }
}

/*void proverka_miller(){
    vector<tuple<unsigned long long, vector<int>, vector<int>>> test = {{13, {2, 3}, {2, 1}}, {29, {2, 7}, {2, 1}}, {61, {2, 3, 5}, {2, 1, 1}}, {6373, {2, 3, 59}, {2, 3, 1}}};
    int sost = 0;
    int  prost = 0;
    int res = 0;
    for (tuple<unsigned long long, vector<int>, vector<int>> now : test){
        for (int i = 0; i < 100000; i++){
            res = test_millera(now, 1);
            if (res == 0) sost++;
            if (res == 1 || res == 2) prost++;
            //else prost++;
        }
        cout << get<0>(now) << " " << fixed << setprecision(3)<< sost  << " " << prost << endl;
        sost = 0;
        prost = 0;
    }
}*/

void fun2(int k, int t, int s){ //k - длина числа в битах, t - параметр надёжности теста Миллера, s - количество раундов теста Миллера-Рабина
    vector<int> control = resheto_eratosfena();
    vector<tuple<unsigned long long, vector<int>, vector<int>>> list_of_N; //вектор чисел  N и канонических разложений N-1
    vector<unsigned long long> list_of_only_N;
    tuple<unsigned long long, vector<int>, vector<int>> N;
    for (int i = 0, n = 0, test; i < 10;){      //заполняем список числами N
        N = generate_N(k, control);
        test = test_millera(N, t);
        if (test != 0 && (count(list_of_only_N.begin(), list_of_only_N.end(), get<0>(N)) == 0)){
            cout << "По тесту Миллера - ";
            test < 2 ? cout << "скорее всего простое" << endl : cout << "точно простое" << endl;
            cout << "По тесту Миллера-Рабина - ";
            cout << test_millera_rabina(get<0>(N), s) << endl;
            cout << N << endl;
            list_of_N.push_back(N);
            list_of_only_N.push_back(get<0>(N));
            i++;
        }
    }
    /*cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    proverka_miller();
    return;*/
}