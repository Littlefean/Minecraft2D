//
// Created by 20281 on 2022/9/12.
//

#ifndef C__LEARN_PRINTER_H
#define C__LEARN_PRINTER_H

#include <windows.h>
#include <iomanip>
#include "Player.h"

void setColor(int a) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}

/**
 * 打印生物的信息
 * @param biology 通常是玩家
 */
void printBiologyData(const Player &biology) {
    // 红色血量
    setColor(4);
    cout << "血：";
    for (int i = 0; i < (int) (biology.hp.value); i++) {
        cout << "Δ";
    }
    cout << endl;
    // 鸡腿
    setColor(6);
    cout << "饱：";
    for (int i = 0; i < (int) (biology.hunger.value); i++) {
        cout << "●";
    }
    cout << endl;
    // 气
    if (biology.state == inWater) {
        setColor(11);
        cout << "气：";
        for (int i = 0; i < (int) (biology.breath.value); i++) {
            cout << "◎";
        }
    }
    setColor(7);
    cout << endl;
    // 物品栏
    cout << "1 2 3 4 5 6 7 8 9 0 " << endl;
    for (GameObject o: biology.item) {
        setColor(o);
        cout << objectToStr[o];
    }
    setColor(7);
    cout << endl;
    for (int i = 0; i < biology.itemIndex; i++) {
        cout << "  ";
    }
    cout << "↑" << endl;

    // 背包
    cout << "packet: {";
    for (auto [k, v]: biology.pack) {
        setColor(k);
        cout << objectToStr[k];
        setColor(7);
        cout << ":" << v << ", ";
    }
    cout << "}" << endl;

    // 手动合成台
    if (!biology.availableList.empty()) {
        cout << "可合成：" << endl;
        for (GameObject newObj: biology.availableList) {
            setColor(newObj);
            cout << objectToStr[newObj];
        }
        setColor(7);
        cout << endl;
        for (int i = 0; i < biology.availableIndex; i++) {
            cout << "  ";
        }
        cout << "↑" << endl;
    } else {
        cout << "当前没有可以合成的物品" << endl;
    }


}

#endif //C__LEARN_PRINTER_H
