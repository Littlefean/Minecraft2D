//
// Created by 20281 on 2022/9/12.
//

#ifndef C__LEARN_BIOLOGY_H
#define C__LEARN_BIOLOGY_H

#include <random>
#include "Vec.h"
#include "ProgressBar.h"
#include "object.h"

#include <windows.h>

enum BiologyState {
    normal = 12,
    inWater = 28,
    burring = 78,
    dead = 71,
};
int biologySeed = 1535;
default_random_engine Eo(biologySeed);

class Biology {
private:


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
    // 可合成的物品列表
    vector<GameObject> availableList{};
    int availableIndex = 0;

    unordered_map<GameObject, int> pack;

    /**
     * 生物构造方法
     * @param loc 位置
     * @param hp 初始化血量
     */
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
     * 挖掘方块
     * 返回这个方块是否被挖碎了
     * @param obj
     *
     */
    bool digBlock(GameObject obj) {
        // 根据手上的工具获取当前的挖掘等级
        int digLevel = 0;
        GameObject tool = this->getHandedObject();
        if (ToolDigLevel.contains(tool)) {
            digLevel = ToolDigLevel[tool];
        }

        int seed = (int) time(nullptr);
        default_random_engine e(seed);
        uniform_real_distribution<double> u(0, 1);
        if (u(e) <= BlockHardnessTable[obj] + digLevel * 0.1) {
            // 挖掘成功
            if (BlockDigCondition[obj] <= digLevel) {
                this->getObject(obj);
            }
            return true;
        } else {
            return false;
        }
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

    /**
     * 更新可合成物品列表
     */
    void updateAvailableList() {
        this->availableList.clear();
        // 遍历配方表里的每一个物品
        for (auto [newObj, recipeMap]: RecipeTable) {
            bool available = true;
            // 遍历合成这个物品的所有配方

            for (auto [needObj, count]: recipeMap) {
                if (this->pack[needObj] >= count) {
                    continue;
                } else {
                    available = false;
                    // cout << "缺少" << objectToStr[needObj] << count - this->pack[needObj] << "个" << endl;
                    break;
                }
            }
            if (available) {
                this->availableList.push_back(newObj);
            } else {
                // cout << "导致";
                // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), newObj);
                // cout << objectToStr[newObj];
                // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                // cout << "无法合成" << endl;
            }
        }
    }

    /**
     * n = 1 , index = 0
     * n = 2 , index = 1
     * ...
     * n = 0 , index = 9
     * @param n 键盘上按下的是数字几？
     */
    void setItemIndex(int n) {
        if (n == 0) {
            this->itemIndex = 9;
        } else {
            this->itemIndex = n - 1;
        }
    }

    void availableItemPlus() {
        if (!this->availableList.empty()) {
            // --->
            this->availableIndex++;
            if (this->availableIndex == this->availableList.size()) {
                availableIndex = 0;
            }
        }
    }

    void availableItemReduce() {
        if (!this->availableList.empty()) {
            // <===
            this->availableIndex--;
            if (this->availableIndex == -1) {
                availableIndex = (int) this->availableList.size() - 1;
            }
        }
    }

    /**
     * 玩家合成物品
     * 默认确保指针指到了正确的物品上
     */
    void getComposeObject() {
        if (this->availableList.empty()) {
            return;
        }
        GameObject gainObj = this->availableList[this->availableIndex];
        for (int i = 0; i < GainCount[gainObj]; i++) {
            this->getObject(gainObj);
        }
        for (auto [useObj, count]: RecipeTable[gainObj]) {
            for (int i = 0; i < count; i++) {
                this->loseObject(useObj);
            }
        }
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
