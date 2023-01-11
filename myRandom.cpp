//
// Created by 20281 on 2023/1/12.
//
#include "myRandom.h"

#include <random>

using namespace std;

int myRandomSeed = (int) time(nullptr);
default_random_engine _E(myRandomSeed);
uniform_real_distribution<double> _U(0, 1);


/**
 * 生成 [0, n) 范围的随机整数
 * @param n
 * @return
 */
int randint(int n) {
    return ((int) _E() % 2147483647) % n;
}

/**
 * 百分之多少的事情发生一件事
 * @param n
 * @return
 */
bool percentage(int n) {
    int r = ((int) _E() % 2147483647) % 100;
    if (r < n) {
        return true;
    }
    return false;
}

/**
 * 返回0~1之间的随机小数
 * @return
 */
double uniform01() {
    return _U(_E);
}
