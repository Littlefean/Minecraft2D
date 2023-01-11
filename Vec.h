//
// Created by 20281 on 2022/9/12.
//

#ifndef C__LEARN_VEC_H
#define C__LEARN_VEC_H

#include <vector>
#include <iostream>
using namespace std;

/**
 * 二维矢量类
 */
class Vec {

public:
    int x;
    int y;

    Vec(int x, int y);

    Vec();

    /**
     * 在 0~width-1 之内，0~height-1之内随机取一个点
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
     * 获取一个坐标点的上下左右四个位置
     * @return
     */
    vector<Vec> getRoundLoc();
};

#endif //C__LEARN_VEC_H
