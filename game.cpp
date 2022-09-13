#include <iostream>
#include "conio.h"  // getch()
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <array>
#include <list>

#include "printer.h"  // 这个必须在第一个

#include "myRandom.h"

#include "Vec.h"
#include "object.h"
#include "Player.h"
#include "worldGenerator.h"
#include "Animal.h"

using namespace std;

class World {
private:
    vector<vector<GameObject>> content;
    int height;
    int width;
    int renderRadius = 5;  // 渲染半径
    Player player{{0, 0}, 10};
    list<Animal> animalList{};  // 动物列表

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

    void animalMove(Animal &a) {
        GameObject hinder = this->getBlock(a.loc.x + a.speed.x, a.loc.y + a.speed.y);
        if (isBlockCanThrough(hinder)) {
            // cout << "动物位置：" << a.loc << "speed:" << a.speed << endl;
            a.go();
            // cout << "动物位置：" << a.loc << "speed:" << a.speed << endl;
        } else {
            // cout << objectToStr[hinder] << "阻碍了牛牛" << endl;
        }
    }

    /// 玩家移动
    void userMove(int dx, int dy) {
        GameObject hinder = this->getBlock(this->player.loc.x + dx, this->player.loc.y + dy);
        if (isBlockCanThrough(hinder)) {
            // 玩家可以移动
            // 玩家移动 受饥饿影响?
            if (this->player.hunger.value <= 3) {
                if (percentage(50)) {
                    return;
                }
            } else if (this->player.hunger.value <= 5) {
                if (percentage(20)) {
                    return;
                }
            }
            this->player.loc.x += dx;
            this->player.loc.y += dy;
            this->player.hunger.change(-0.01);
            // 前方方块是否是掉落物？
            if (isBlockCanPickUp(hinder)) {
                this->setBlock(air, this->player.loc.x, this->player.loc.y);
                this->player.getObject(hinder);
            }

        } else {
            // 玩家被阻挡不能移动
        }
    }

public:
    /**
     * 生成一个世界
     * @param w 宽度
     * @param h 高度
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

        for (int i = 0; i < 5; i++) {
            Vec randLoc = Vec::randomVec(this->width, this->height);
            if (this->getBlock(randLoc) == air) {
                this->animalList.insert(this->animalList.end(), Animal(sheep, randLoc));
            } else {
                i--;
            }
        }

        // 寻找出生点
        int centerX = this->width / 2;
        int centerY = this->height / 2;
        // 寻找距离中心点最近的空气点
        for (int r = 1; r < 20; r++) {
            for (int y = centerX - r; y <= centerX + r; y++) {
                for (int x = centerY - r; x <= centerY + r; x++) {
                    if (this->getBlock(x, y) == air) {
                        this->player.loc.x = x;
                        this->player.loc.y = y;
                        return;
                    }
                }
            }
        }
    }

    /**
     * 打印完整地形
     */
    void showAll() {
        for (int y = 0; y < this->height; y++) {
            for (int x = 0; x < this->width; x++) {
                if (x == this->player.loc.x && y == this->player.loc.y) {
                    // 优先显示玩家
                    setColor(normal);
                    cout << "您";
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
            setColor(7); // 7 是正常的颜色
            cout << endl;
        }
        cout << "=====" << endl;
    }

    /**
     * 展示第一视角地图
     */
    void show1() {
        for (int dy = -this->renderRadius; dy <= this->renderRadius; dy++) {
            for (int dx = -this->renderRadius; dx <= this->renderRadius; dx++) {
                // x, y 分别是现在需要打印的位置
                const int x = this->player.loc.x + dx;
                const int y = this->player.loc.y + dy;

                if (dx == 0 && dy == 0) {
                    // 优先显示玩家
                    // 根据玩家状态显示颜色
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
                    // 优先显示动物
                    bool haveAnimal = false;
                    GameObject aniObj;

                    for (const Animal &a: this->animalList) {
                        if (a.loc.x == x && a.loc.y == y) {
                            haveAnimal = true;  // todo 这里的a.loc 确实是在发生变化的
                            aniObj = a.showChar;
                            // cout << a.loc << endl;
                            break;
                        }
                    }
                    if (haveAnimal) {
                        setColor(aniObj);

                        cout << objectToStr[aniObj];

                    } else {
                        // 最后显示方块
                        GameObject thing = this->getBlock(x, y);
                        setColor(thing);
                        if (objectToStr.count(thing)) {
                            cout << objectToStr[thing];
                        } else {
                            cout << "??";
                        }
                    }

                }
            }
            setColor(7); // 7 是正常的颜色
            cout << endl;
        }
        // 打印玩家状态
        printBiologyData(this->player);
    }

    /**
     * 判断一个叶子是不是没有连接着根部
     * 快死了
     */
    bool isLeaveLossRoot(Vec location) {
        if (this->getBlock(location.x, location.y) == leave) {
            // 如果当前位置是一个叶子，bfs周围5距离内是否有树木或叶子，如果没有则死亡
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
     * 世界进行一次演化
     */
    void tick() {
        // 玩家状态更新
        this->player.updateAvailableList();
        // 气的关系
        if (this->getBlock(this->player.loc) == water) {
            this->player.breath.change(-1);
        } else {
            this->player.breath.setMax();
        }
        // 气血关系
        if (this->player.breath.value == 0) {
            this->player.hp.change(-1);
        }
        // 饱食度和血的关系
        if (this->player.hunger.value == 0) {
            this->player.hp.change(-0.1);
        }
        if (!this->player.hp.isMax()) {
            if (this->player.hunger.value > 9) {
                this->player.hp.change(0.5);
                this->player.hunger.change(-0.5);
            }
        }
        // 血量和游戏的关系
        if (this->player.hp.value == 0) {
            cout << "game Over!!!" << endl;
        }
        // 动物更新 todo
        for (Animal &a: this->animalList) {
            a.tickAction();
            // 移动动物
            this->animalMove(a);
        }
        // 植被更新
        int updateRange = this->renderRadius + 2;
        for (int y = this->player.loc.y - updateRange; y <= this->player.loc.y + updateRange; y++) {
            for (int x = this->player.loc.x - updateRange; x <= this->player.loc.x + updateRange; x++) {
                if (this->getBlock(x, y) == leave) {
                    if (this->isLeaveLossRoot(Vec(x, y))) {
                        // 有20%的几率销毁
                        if (percentage(20)) {
                            this->setBlock(air, x, y);
                            // 销毁之后 可能产生树苗、果子
                            if (percentage(25)) {
                                this->setBlock(apple, x, y);
                            } else if (percentage(25)) {
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

    /**
     * 开始游戏
     * 进入按键监听，循环状态
     */
    void play() {
        while (true) {
            int key = getch();
            if (key == 27) {
                // exit
                break;
            }
            if (48 <= key && key <= 57) {
                // 数字 切换物品栏指针
                this->player.setItemIndex(key - 48);
            }
            if (key == 97) {
                // a 切换合成物 左侧
                this->player.availableItemReduce();
            }
            if (key == 100) {
                // d 切换合成物 右侧
                this->player.availableItemPlus();
            }
            if (key == 99) {
                // c 合成物品
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
                    // z 使用左键攻击、挖掘
                    if (isBlockCanDig(hinder)) {
                        // 玩家可以破坏方块
                        if (this->player.digBlock(hinder)) {
                            // 破坏成功
                            this->setBlock(air, playerFacedLoc);
                        }
                        this->player.hunger.change(-0.2);
                    }
                }
                if (key == 13) {
                    // x 使用右键
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
                /// 移动
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
    cout << "正在开始游戏" << endl;
    World g(30, 30);
    g.show1();
    g.play();
    // g.testPlay();
    // for (int i = 0; i < 10; i++) {
    //     g.showAll();
    //     g.tick();
    // }
    return 0;
}