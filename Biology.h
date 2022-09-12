//
// Created by 20281 on 2022/9/12.
//

#ifndef C__LEARN_BIOLOGY_H
#define C__LEARN_BIOLOGY_H

#include "Vec.h"
#include "ProgressBar.h"
#include "object.h"

enum BiologyState {
    normal = 12,
    inWater = 28,
    burring = 78,
    dead = 71,
};

class Biology {

public:

    Vec loc{0, 0};
    Vec speed{1, 0};
    ProgressBar hp = ProgressBar{10.0, 10.0};
    ProgressBar hunger = ProgressBar{10.0, 10.0};
    ProgressBar breath = ProgressBar{10.0, 10.0};
    BiologyState state = normal;
    // 物品栏
    vector<GameObject> item = {air, air, air, air, air, air, air, air, air, air};
    int itemIndex = 0;  // 当前选定的是哪个
    unordered_map<GameObject, int> pack;

    Biology(Vec loc, double hp) {
        this->loc = loc;
        this->speed = {1, 0};
        this->hp = ProgressBar{hp, hp};
        this->hunger = ProgressBar{10.0, 10.0};
        this->breath = ProgressBar{10.0, 10.0};
        this->state = normal;
    }

    /**
     * 玩家获得物品进入背包
     * @param obj 获得的物品
     */
    void getObject(GameObject obj) {
        if (this->pack.count(obj)) {
            // 已经有了的物品

        } else {
            // 还没有
            for (auto &i: this->item) {
                if (i == air) {
                    i = obj;
                    break;
                }
            }
        }
        this->pack[obj]++;
    }

    /**
     * 玩家失去一个物品
     * @param obj
     */
    void loseObject(GameObject obj) {
        if (this->pack.count(obj)) {
            this->pack[obj]--;
            if (this->pack[obj] <= 0) {
                // 删除这个键值对
                this->pack.erase(this->pack.find(obj));
                // 丢光了
                for (auto &i: this->item) {
                    if (i == obj) {
                        i = air;
                        break;
                    }
                }
            }
        } else {
            cout << "玩家本来没有这个物品你却还要失去它" << endl;
            raise(101);
        }
    }

    /**
     * 获取玩家现在手上的物品
     */
    GameObject getHandedObject() {
        return this->item[this->itemIndex];
    }

    void itemIndexPlus() {
        this->itemIndex++;
        if (this->itemIndex == this->item.size()) {
            this->itemIndex = 0;
        }
    }

    void itemIndexReduce() {
        this->itemIndex--;
        if (this->itemIndex == -1) {
            this->itemIndex = (int) this->item.size() - 1;
        }
    }

    /**
     * 玩家吃物品
     * 保证玩家现在手里有这个物品
     * @param o
     */
    void eat(GameObject o) {
        this->hunger.change(foodTastiness[o]);
        this->loseObject(o);
    }
};

#endif //C__LEARN_BIOLOGY_H
