// ����������߿�
// ��ģ���к���ȫ���������
// Created by 20281 on 2022/9/13.
//

#ifndef C__LEARN_MYRANDOM_H
#define C__LEARN_MYRANDOM_H

#include <random>

using namespace std;

int myRandomSeed = (int) time(nullptr);
default_random_engine _E(myRandomSeed);
uniform_real_distribution<double> _U(0, 1);

/**
 * ���� [0, n) ��Χ���������
 * @param n
 * @return
 */
int randint(int n) {
    return ((int) _E() % 2147483647) % n;
}

/**
 * �ٷ�֮���ٵ����鷢��һ����
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
 * ����0~1֮������С��
 * @return
 */
double uniform01() {
    return _U(_E);
}


// double randRate() {
//
// }

#endif //C__LEARN_MYRANDOM_H
