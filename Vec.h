//
// Created by 20281 on 2022/9/12.
//

#ifndef C__LEARN_VEC_H
#define C__LEARN_VEC_H

#include <vector>
#include "myRandom.h"

using namespace std;


class Vec {

public:
    int x;
    int y;

    Vec(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Vec() {
        this->x = 0;
        this->y = 0;
    }

    /**
     * 在 0~width-1 之内，0~height-1之内随机取一个点
     * @param width
     * @param height
     * @return
     */
    static Vec randomVec(int width, int height) {
        return Vec{randint(width), randint(height)};
    }

    bool operator<(const Vec &v) const {
        if (this->x < v.x)return true;
        if (this->x > v.x)return false;
        if (this->y < v.y)return true;
        return false;
    }

    Vec operator+(const Vec &v) const {
        Vec res{this->x + v.x, this->y + v.y};
        return res;
    }

    bool operator==(const Vec &v) const {
        return v.x == this->x && v.y == this->y;
    }

    friend ostream &operator<<(ostream &os, const Vec &p) {
        return os << "(" << p.x << "," << p.y << ")";
    };

    vector<Vec> getRoundLoc() {
        vector<Vec> res;
        res.emplace_back(this->x + 1, this->y);
        res.emplace_back(this->x - 1, this->y);
        res.emplace_back(this->x, this->y + 1);
        res.emplace_back(this->x, this->y - 1);
        return res;
    }
};

#endif //C__LEARN_VEC_H
