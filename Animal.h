//
// Created by 20281 on 2022/9/13.
//

#ifndef C__LEARN_ANIMAL_H
#define C__LEARN_ANIMAL_H

#include "myRandom.h"

#include "object.h"
#include "Vec.h"
#include "ProgressBar.h"


class Animal {
private:
    // int damage = 2;

public:
    GameObject showChar;
    Vec loc{0, 0};
    Vec speed{0, 1};
    ProgressBar hp{10, 10};
    unordered_map<GameObject, int> deadObjects;

    /**
     * ��������������
     */
    void setDeadObj(GameObject o, int count) {
        deadObjects[o] = count;
    }

    void go() {
        // cout << "����λ�ã�" << this->loc << "speed:" << this->speed << endl;
        this->loc.x += this->speed.x;
        this->loc.y += this->speed.y;
        // cout << "����λ�ã�" << this->loc << "speed:" << this->speed << endl;
    }

    /**
     * һ��ʱ��̵���Ϊ
     */
    void tickAction() {
        // ���������ƶ����ڴ˺�����ֻ�Ǹ����ƶ��Ķ���

        int r = randint(4);
        switch (r) {
            case 0:
                this->speed = Vec{0, 1};
                break;
            case 1:
                this->speed = Vec{0, -1};
                break;
            case 2:
                this->speed = Vec{1, 0};
                break;

            case 3:
                this->speed = Vec{-1, 0};
                break;
            default:
                this->speed = Vec{0, 1};
        }
        // this->loc.x += this->speed.x;
        // this->loc.y += this->speed.y;

    }

    Animal(GameObject o, Vec loc) {
        this->showChar = o;
        this->loc = loc;
    }

};

#endif //C__LEARN_ANIMAL_H
