//
// Created by 20281 on 2022/9/12.
//

#ifndef C__LEARN_VEC_H
#define C__LEARN_VEC_H

#include <vector>
#include <iostream>
using namespace std;

/**
 * ��άʸ����
 */
class Vec {

public:
    int x;
    int y;

    Vec(int x, int y);

    Vec();

    /**
     * �� 0~width-1 ֮�ڣ�0~height-1֮�����ȡһ����
     * @param width
     * @param height
     * @return
     */
    static Vec randomVec(int width, int height);

    bool operator<(const Vec &v) const;

    Vec operator+(const Vec &v) const;

    bool operator==(const Vec &v) const;

    friend ostream &operator<<(ostream &os, const Vec &p);

    /**
     * ��ȡһ�����������������ĸ�λ��
     * @return
     */
    vector<Vec> getRoundLoc();
};

#endif //C__LEARN_VEC_H
