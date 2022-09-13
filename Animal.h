//
// Created by 20281 on 2022/9/13.
//

#ifndef C__LEARN_ANIMAL_H
#define C__LEARN_ANIMAL_H

#include "object.h"
#include "Vec.h"
#include "ProgressBar.h"

class Animal {
private:
    int damage = 2;
public:
    GameObject showChar;
    Vec loc{0, 0};
    Vec targetLoc{};
    ProgressBar hp{10, 10};
    unordered_map<GameObject, int> deadObjects;
    // vector<vector<GameObject>> &viewWorld; // 视野世界

    /**
     * 一个时间刻的行为
     */
    void tickAction() {
        // 上下左右移动

    }

    Animal(GameObject o, Vec loc) {
        this->showChar = o;
        this->loc = loc;
        this->targetLoc = loc;
    }

};

#endif //C__LEARN_ANIMAL_H
