#include "general_fun.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include <random>

using namespace std;

int len_in_bit(unsigned long long a){
    int result = 0;
    while (a != 0){
        result++;
        a /= 2;
    }
    return result;
}

vector<int> resheto_eratosfena(){
    vector<int> result = {1};

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

unsigned long long num_exp(unsigned long a, unsigned long n, unsigned long p){
    if (a < 0 || n < 1 || p < 1){
        cout << "Ошибка, числа не должны быть отрицательными" << endl;
        return 0;
    } 
    vector<int> n_bin;
    while(n != 0){ //находим двоичное представление степени
        n_bin.push_back(n%2);
        n /= 2;
        
    }
    unsigned long long result = 1;
    for (int i : n_bin){
        if (i == 1) result = result * a % p;
        a = a*a%p;
    }
    return result;
}



string test_millera_rabina(unsigned long long n, int k){ //n - число на проверку, k - число раундов, вероятность ошибки = 4^(-k)  (k = 2, вероятность = 0.0625)
    int s = 0;
    unsigned long long t = n - 1;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> random_num(2, 999999);
    if (len_in_bit(n) < 32) {
        random_num.param(uniform_int_distribution<>::param_type(2, n-2));
    }
    for (;t%2 == 0;){ //ищем  s такое что 2^(s)*t = n
        s++;
        t /= 2;
    }
    unsigned long long x = 0;
    for (int i = 0; i < k; i++){
        x = num_exp(random_num(gen), t, n);
        if (x == 1 || x == n-1) continue;

        bool composite = true;
        for (unsigned long long j = 0; j < s-1; j++) {
            x = num_exp(x, 2, n);
            if (x == 1) return "составное";
            if (x == n-1) {
                composite = false;
                break;
            }
        }
        if (composite) return "составное";
    }
    return "вероятно простое";
}