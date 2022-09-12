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
    // ��Ʒ��
    vector<GameObject> item = {air, air, air, air, air, air, air, air, air, air};
    int itemIndex = 0;  // ��ǰѡ�������ĸ�
    // �ɺϳɵ���Ʒ�б�
    vector<GameObject> availableList{};
    int availableIndex = 0;

    unordered_map<GameObject, int> pack;

    /**
     * ���ﹹ�췽��
     * @param loc λ��
     * @param hp ��ʼ��Ѫ��
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
     * ��һ����Ʒ���뱳��
     * @param obj ��õ���Ʒ
     */
    void getObject(GameObject obj) {
        if (this->pack.count(obj)) {
            // �Ѿ����˵���Ʒ

        } else {
            // ��û��
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
     * �ھ򷽿�
     * ������������Ƿ�������
     * @param obj
     *
     */
    bool digBlock(GameObject obj) {
        // �������ϵĹ��߻�ȡ��ǰ���ھ�ȼ�
        int digLevel = 0;
        GameObject tool = this->getHandedObject();
        if (ToolDigLevel.contains(tool)) {
            digLevel = ToolDigLevel[tool];
        }

        int seed = (int) time(nullptr);
        default_random_engine e(seed);
        uniform_real_distribution<double> u(0, 1);
        if (u(e) <= BlockHardnessTable[obj] + digLevel * 0.1) {
            // �ھ�ɹ�
            if (BlockDigCondition[obj] <= digLevel) {
                this->getObject(obj);
            }
            return true;
        } else {
            return false;
        }
    }

    /**
     * ���ʧȥһ����Ʒ
     * @param obj
     */
    void loseObject(GameObject obj) {
        if (this->pack.count(obj)) {
            this->pack[obj]--;
            if (this->pack[obj] <= 0) {
                // ɾ�������ֵ��
                this->pack.erase(this->pack.find(obj));
                // ������
                for (auto &i: this->item) {
                    if (i == obj) {
                        i = air;
                        break;
                    }
                }
            }
        } else {
            cout << "��ұ���û�������Ʒ��ȴ��Ҫʧȥ��" << endl;
            raise(101);
        }
    }

    /**
     * ��ȡ����������ϵ���Ʒ
     */
    GameObject getHandedObject() {
        return this->item[this->itemIndex];
    }

    /**
     * ���¿ɺϳ���Ʒ�б�
     */
    void updateAvailableList() {
        this->availableList.clear();
        // �����䷽�����ÿһ����Ʒ
        for (auto [newObj, recipeMap]: RecipeTable) {
            bool available = true;
            // �����ϳ������Ʒ�������䷽

            for (auto [needObj, count]: recipeMap) {
                if (this->pack[needObj] >= count) {
                    continue;
                } else {
                    available = false;
                    // cout << "ȱ��" << objectToStr[needObj] << count - this->pack[needObj] << "��" << endl;
                    break;
                }
            }
            if (available) {
                this->availableList.push_back(newObj);
            } else {
                // cout << "����";
                // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), newObj);
                // cout << objectToStr[newObj];
                // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                // cout << "�޷��ϳ�" << endl;
            }
        }
    }

    /**
     * n = 1 , index = 0
     * n = 2 , index = 1
     * ...
     * n = 0 , index = 9
     * @param n �����ϰ��µ������ּ���
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
     * ��Һϳ���Ʒ
     * Ĭ��ȷ��ָ��ָ������ȷ����Ʒ��
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
     * ��ҳ���Ʒ
     * ��֤������������������Ʒ
     * @param o
     */
    void eat(GameObject o) {
        this->hunger.change(foodTastiness[o]);
        this->loseObject(o);
    }
};

#endif //C__LEARN_BIOLOGY_H
