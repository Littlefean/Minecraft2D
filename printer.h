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
 * ��ӡ�������Ϣ
 * @param biology ͨ�������
 */
void printBiologyData(const Player &biology) {
    // ��ɫѪ��
    setColor(4);
    cout << "Ѫ��";
    for (int i = 0; i < (int) (biology.hp.value); i++) {
        cout << "��";
    }
    cout << endl;
    // ����
    setColor(6);
    cout << "����";
    for (int i = 0; i < (int) (biology.hunger.value); i++) {
        cout << "��";
    }
    cout << endl;
    // ��
    if (biology.state == inWater) {
        setColor(11);
        cout << "����";
        for (int i = 0; i < (int) (biology.breath.value); i++) {
            cout << "��";
        }
    }
    setColor(7);
    cout << endl;
    // ��Ʒ��
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
    cout << "��" << endl;

    // ����
    cout << "packet: {";
    for (auto [k, v]: biology.pack) {
        setColor(k);
        cout << objectToStr[k];
        setColor(7);
        cout << ":" << v << ", ";
    }
    cout << "}" << endl;

    // �ֶ��ϳ�̨
    if (!biology.availableList.empty()) {
        cout << "�ɺϳɣ�" << endl;
        for (GameObject newObj: biology.availableList) {
            setColor(newObj);
            cout << objectToStr[newObj];
        }
        setColor(7);
        cout << endl;
        for (int i = 0; i < biology.availableIndex; i++) {
            cout << "  ";
        }
        cout << "��" << endl;
    } else {
        cout << "��ǰû�п��Ժϳɵ���Ʒ" << endl;
    }


}

#endif //C__LEARN_PRINTER_H
