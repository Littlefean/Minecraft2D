#include <iostream>
#include "conio.h"  // getch()
#include <vector>
#include <map>
#include <set>
#include <random>
#include <queue>
#include <array>

#include "printer.h"

#include "Vec.h"
#include "object.h"
#include "Biology.h"
#include "worldGenerator.h"

using namespace std;
int seed = 15535;
default_random_engine E(seed);


class World {
private:
    vector<vector<GameObject>> content;
    int height;
    int width;
    int renderRadius = 5;  // ��Ⱦ�뾶
    Biology player{{0, 0}, 10};

    void setBlock(GameObject n, int x, int y) {
        if ((0 <= x && x < this->width) && (0 <= y && y < this->height)) {
            this->content[y][x] = n;
        }
    }

    void setBlock(GameObject n, Vec loc) {
        if ((0 <= loc.x && loc.x < this->width) && (0 <= loc.y && loc.y < this->height)) {
            this->content[loc.y][loc.x] = n;
        }
    }


    GameObject getBlock(int x, int y) {
        if ((0 <= x && x < this->width) && (0 <= y && y < this->height)) {
            return this->content[y][x];
        } else {
            return barrier;
        }
    }

    GameObject getBlock(Vec loc) {
        if ((0 <= loc.x && loc.x < this->width) && (0 <= loc.y && loc.y < this->height)) {
            return this->content[loc.y][loc.x];
        } else {
            return barrier;
        }
    }

    /// ����ƶ�
    void userMove(int dx, int dy) {
        GameObject hinder = this->getBlock(this->player.loc.x + dx, this->player.loc.y + dy);
        if (isBlockCanThrough(hinder)) {
            // ��ҿ����ƶ�
            // ����ƶ� �ܼ���Ӱ��?
            if (this->player.hunger.value <= 3) {
                if (E() % 2 == 0) {
                    return;
                }
            } else if (this->player.hunger.value <= 5) {
                if (E() % 5 == 0) {
                    return;
                }
            }
            this->player.loc.x += dx;
            this->player.loc.y += dy;
            this->player.hunger.change(-0.01);
            // ǰ�������Ƿ��ǵ����
            if (isBlockCanPickUp(hinder)) {
                this->setBlock(air, this->player.loc.x, this->player.loc.y);
                this->player.getObject(hinder);
            }

        } else {
            // ��ұ��赲�����ƶ�
        }
    }

public:
    /**
     * ����һ������
     * @param w ���
     * @param h �߶�
     */
    World(int w, int h) {
        this->height = h;
        this->width = w;

        for (int y = 0; y < this->height; y++) {
            vector<GameObject> line;
            for (int x = 0; x < this->width; x++) {
                line.push_back(air);
            }
            this->content.push_back(line);
        }

        WorldGenerator::mountain(this->content);
        WorldGenerator::genOre(this->content);
        WorldGenerator::planTree(this->content);
        WorldGenerator::pool(this->content);
        // Ѱ�ҳ�����
        this->player.loc.x = this->width / 2;
        this->player.loc.y = this->height / 2;
    }

    /**
     * ��ӡ��������
     */
    void showAll() {
        for (int y = 0; y < this->height; y++) {
            for (int x = 0; x < this->width; x++) {
                if (x == this->player.loc.x && y == this->player.loc.y) {
                    // ������ʾ���
                    setColor(normal);
                    cout << "��";
                } else {
                    GameObject thing = this->getBlock(x, y);
                    setColor(thing);
                    if (objectToStr.count(thing)) {
                        cout << objectToStr[thing];
                    } else {
                        cout << '?';
                    }
                }
            }
            setColor(7); // 7 ����������ɫ
            cout << endl;
        }
        cout << "=====" << endl;
    }

    /**
     * չʾ��һ�ӽǵ�ͼ
     */
    void show1() {
        for (int dy = -this->renderRadius; dy <= this->renderRadius; dy++) {
            for (int dx = -this->renderRadius; dx <= this->renderRadius; dx++) {
                int x = this->player.loc.x + dx;
                int y = this->player.loc.y + dy;

                if (x == this->player.loc.x && y == this->player.loc.y) {
                    // ������ʾ���
                    // �������״̬��ʾ��ɫ
                    if (this->getBlock(this->player.loc) == water) {
                        this->player.state = inWater;
                        setColor(inWater);
                    } else {
                        this->player.state = normal;
                        setColor(normal);
                    }
                    if (this->player.speed == Vec{0, 1}) {
                        cout << "VV";
                    } else if (this->player.speed == Vec{0, -1}) {
                        cout << "AA";
                    } else if (this->player.speed == Vec{1, 0}) {
                        cout << "=>";
                    } else if (this->player.speed == Vec{-1, 0}) {
                        cout << "<=";
                    }
                } else {
                    GameObject thing = this->getBlock(x, y);
                    setColor(thing);
                    if (objectToStr.count(thing)) {
                        cout << objectToStr[thing];
                    } else {
                        cout << '?';
                    }
                }
            }
            setColor(7); // 7 ����������ɫ
            cout << endl;
        }
        // ��ӡ���״̬
        printBiologyData(this->player);
    }

    /**
     * �ж�һ�����ǲ���û�������Ÿ���
     * ������
     */
    bool isLeaveLossRoot(Vec location) {
        if (this->getBlock(location.x, location.y) == leave) {
            // �����ǰλ����һ���ݣ�bfs��Χ5�������Ƿ�����ľ��ݵأ����û��������
            queue<pair<Vec, int>> q;
            set<Vec> vecSet{Vec(location.x, location.y)};
            q.push({Vec(location.x, location.y), 0});
            while (!q.empty()) {
                auto [loc, r] = q.front();
                q.pop();
                GameObject o = this->getBlock(loc.x, loc.y);
                if (r > 3)
                    continue;
                if (o != wood && o != leave)
                    continue;
                if (o == wood)
                    return false;
                else {
                    for (Vec roundLoc: loc.getRoundLoc()) {
                        if (vecSet.count(roundLoc) != 0)
                            continue;
                        q.push(make_pair(roundLoc, r + 1));
                        vecSet.insert(roundLoc);
                    }
                }
            }
            return true;
        } else {
            return false;
        }
    }

    /**
     * �������һ���ݻ�
     */
    void tick() {
        // ���״̬����
        this->player.updateAvailableList();
        // ���Ĺ�ϵ
        if (this->getBlock(this->player.loc) == water) {
            this->player.breath.change(-1);
        } else {
            this->player.breath.setMax();
        }
        // ��Ѫ��ϵ
        if (this->player.breath.value == 0) {
            this->player.hp.change(-1);
        }
        // ��ʳ�Ⱥ�Ѫ�Ĺ�ϵ
        if (this->player.hunger.value == 0) {
            this->player.hp.change(-0.1);
        }
        if (!this->player.hp.isMax()) {
            if (this->player.hunger.value > 9) {
                this->player.hp.change(0.5);
                this->player.hunger.change(-0.5);
            }
        }
        // Ѫ������Ϸ�Ĺ�ϵ
        if (this->player.hp.value == 0) {
            cout << "game Over!!!" << endl;
        }
        // ֲ������
        int updateRange = this->renderRadius + 2;
        for (int y = this->player.loc.y - updateRange; y <= this->player.loc.y + updateRange; y++) {
            for (int x = this->player.loc.x - updateRange; x <= this->player.loc.x + updateRange; x++) {
                if (this->getBlock(x, y) == leave) {
                    if (this->isLeaveLossRoot(Vec(x, y))) {
                        // ��20%�ļ�������
                        if (E() % 5 == 0) {
                            this->setBlock(air, x, y);
                            // ����֮�� ���ܲ������硢����
                            if (E() % 4 == 0) {
                                this->setBlock(apple, x, y);
                            } else if (E() % 4 == 1) {
                                this->setBlock(sapling, x, y);
                            }
                        }
                    }
                }
            }
        }
    }

    void testPlay() {
        while (true) {
            char key;
            cin >> key;
            this->tick();
            switch (key) {
                case 'q':
                    return;
                case 'w':
                    this->userMove(0, -1);
                    break;
                case 's':
                    this->userMove(0, 1);
                    break;
                case 'a':
                    this->userMove(-1, 0);
                    break;
                case 'd':
                    this->userMove(1, 0);
                    break;
                default:
                    break;
            }
            this->showAll();
        }
    }

    void play() {
        while (true) {
            int key = getch();
            if (key == 27) {
                // exit
                break;
            }
            if (48 <= key && key <= 57) {
                // ���� �л���Ʒ��ָ��
                this->player.setItemIndex(key - 48);
            }
            if (key == 97) {
                // a �л��ϳ��� ���
                this->player.availableItemReduce();
            }
            if (key == 100) {
                // d �л��ϳ��� �Ҳ�
                this->player.availableItemPlus();
            }
            if (key == 99) {
                // c �ϳ���Ʒ
                this->player.getComposeObject();
            }
            if (key == 224) {
                continue;
            } else {
                // tick
                system("cls");
                this->tick();
                Vec playerFacedLoc = this->player.loc + this->player.speed;
                GameObject hinder = this->getBlock(playerFacedLoc);
                if (key == 32) {
                    // z ʹ������������ھ�
                    if (isBlockCanDig(hinder)) {
                        // ��ҿ����ƻ�����
                        if (this->player.digBlock(hinder)) {
                            // �ƻ��ɹ�
                            this->setBlock(air, playerFacedLoc);
                        }
                        this->player.hunger.change(-0.2);
                    }
                }
                if (key == 13) {
                    // x ʹ���Ҽ�
                    GameObject handObj = this->player.getHandedObject();
                    if (isEatable(handObj)) {
                        this->player.eat(handObj);
                    } else if (isBlockPut(handObj) && isBlockBeCover(hinder)) {
                        this->setBlock(handObj, playerFacedLoc);
                        this->player.loseObject(handObj);
                    } else {

                    }
                    this->player.hunger.change(-0.05);
                }
                /// �ƶ�
                if (key == 72) {
                    // up
                    if (this->player.speed.x == 0 && this->player.speed.y == -1) {
                        this->userMove(0, -1);
                    } else {
                        this->player.speed.x = 0;
                        this->player.speed.y = -1;
                    }

                } else if (key == 80) {
                    // down
                    if (this->player.speed.x == 0 && this->player.speed.y == 1) {
                        this->userMove(0, 1);
                    } else {
                        this->player.speed.x = 0;
                        this->player.speed.y = 1;
                    }
                } else if (key == 75) {
                    // left
                    if (this->player.speed.x == -1 && this->player.speed.y == 0) {
                        this->userMove(-1, 0);
                    } else {
                        this->player.speed.x = -1;
                        this->player.speed.y = 0;
                    }
                } else if (key == 77) {
                    // right
                    if (this->player.speed.x == 1 && this->player.speed.y == 0) {
                        this->userMove(1, 0);
                    } else {
                        this->player.speed.x = 1;
                        this->player.speed.y = 0;
                    }
                }
                this->show1();
                cout << key << endl;
            }
        }
    }
};


int main() {
    cout << "���ڿ�ʼ��Ϸ" << endl;
    World g(100, 100);
    g.show1();
    g.play();
    // g.testPlay();
    // for (int i = 0; i < 10; i++) {
    //     g.showAll();
    //     g.tick();
    // }
    return 0;
}