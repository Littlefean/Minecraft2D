//
// Created by 20281 on 2022/9/12.
//

#ifndef C__LEARN_VEC_H
#define C__LEARN_VEC_H

#include <vector>

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
