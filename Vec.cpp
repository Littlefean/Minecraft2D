//
// Created by 20281 on 2023/1/12.
//


#include <vector>
#include <iostream>
#include "myRandom.h"
#include "Vec.h"

using namespace std;


Vec::Vec(int x, int y) {
    this->x = x;
    this->y = y;
}

Vec::Vec() {
    this->x = 0;
    this->y = 0;
}

/**
 * 在 0~width-1 之内，0~height-1之内随机取一个点
 * @param width
 * @param height
 * @return
 */
Vec Vec::randomVec(int width, int height) {
    return Vec{randint(width), randint(height)};
}

bool Vec::operator<(const Vec &v) const {
    if (this->x < v.x)return true;
    if (this->x > v.x)return false;
    if (this->y < v.y)return true;
    return false;
}

Vec Vec::operator+(const Vec &v) const {
    Vec res{this->x + v.x, this->y + v.y};
    return res;
}

bool Vec::operator==(const Vec &v) const {
    return v.x == this->x && v.y == this->y;
}

ostream &operator<<(ostream &os, const Vec &p) {
    return os << "(" << p.x << "," << p.y << ")";
};

/**
 * 获取一个坐标点的上下左右四个位置
 * @return
 */
vector<Vec> Vec::getRoundLoc() {
    vector<Vec> res;
    res.emplace_back(this->x + 1, this->y);
    res.emplace_back(this->x - 1, this->y);
    res.emplace_back(this->x, this->y + 1);
    res.emplace_back(this->x, this->y - 1);
    return res;
}


