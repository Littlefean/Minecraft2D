//
// 世界生成器
// Created by 20281 on 2022/9/12.
//

#ifndef C__LEARN_WORLDGENERATOR_H
#define C__LEARN_WORLDGENERATOR_H


#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include "myRandom.h"


#include "Vec.h"
#include "object.h"

using namespace std;

/**
 * 平滑函数，仅限此文件内部使用
 * @param xi
 * @return
 */
double smoothFunc(double xi) {
    return 3 * pow(xi, 2) - 2 * pow(xi, 3);
}

/**
 * 二维噪音类
 */
class Noise2D {
    int diff;  // 间距
    double loud;  // 响度
    int seed;

    /**
     * 传入一个坐标，返回这个坐标所在区域的四个角落噪音源头位置
     * @param x 坐标
     * @param y 坐标
     * @return 四个源头位置组成的vector
     */
    [[nodiscard]] vector<Vec> getNoisePosition(int x, int y) const {
        int xMin, xMax, yMin, yMax;
        if (x % this->diff == 0) {
            xMin = x;
            xMax = x + this->diff;
        } else {
            xMin = x - x % this->diff;
            xMax = xMin + this->diff;
        }
        if (y % this->diff == 0) {
            yMin = y;
            yMax = y + this->diff;
        } else {
            yMin = y - y % this->diff;
            yMax = yMin + this->diff;
        }
        vector<Vec> res{};
        // 左上 右上 左下 右下
        res.emplace_back(xMin, yMax);
        res.emplace_back(xMax, yMax);
        res.emplace_back(xMin, yMin);
        res.emplace_back(xMax, yMin);
        return res;
    }

    /**
     * 获取一个源头的噪音值
     * @param x 坐标
     * @param y 坐标
     * @return 噪音值
     */
    double getCoreNoise(int x, int y) {
        vector<Vec> p4 = this->getNoisePosition(x, y);
        for (Vec p: p4) {
            if (p == Vec(x, y)) {
                ostringstream os;
                os << x << '-' << y << '-' << this->seed;
                unsigned long long se = hash<string>{}(os.str());
                default_random_engine e(se);
                uniform_real_distribution<double> u(0, 1);
                return (u(e) * 2 - 1) * this->loud;
            }
        }
        return 0;
    }

public:
    /**
     * 二维噪音类的构造方法
     * @param diff 间距
     * @param loud 响度
     * @param seed 种子
     */
    Noise2D(int diff, double loud, int seed) {  // todo seed type
        this->diff = diff;
        this->loud = loud;
        this->seed = seed;
    }

    /**
     * 获取某个位置上的buff
     * @param x 坐标
     * @param y 坐标
     * @return buff
     */
    double getBuff(int x, int y) {
        vector<Vec> noises = this->getNoisePosition(x, y);
        Vec p1 = noises[0];
        Vec p2 = noises[1];
        Vec p3 = noises[2];
        Vec p4 = noises[3];
        int xMin, yMin;
        xMin = p1.x;
        yMin = p4.y;
        double qRight = smoothFunc((float) (x - xMin) / (float) this->diff);
        double qLeft = 1 - qRight;
        double qTop = smoothFunc((float) (y - yMin) / (float) this->diff);
        double qDown = 1 - qTop;
        double n1, n2, n3, n4;
        n1 = this->getCoreNoise((int) p1.x, (int) p1.y);
        n2 = this->getCoreNoise((int) p2.x, (int) p2.y);
        n3 = this->getCoreNoise((int) p3.x, (int) p3.y);
        n4 = this->getCoreNoise((int) p4.x, (int) p4.y);
        return n1 * (qLeft * qTop) +
               n2 * (qRight * qTop) +
               n3 * (qLeft * qDown) +
               n4 * (qRight * qDown);
    }
};

/**
 * 二维噪音集类
 */
class NoiseSet2D {

public:
    double seed;
    // 这个二维噪音集的所有单层二维噪音
    vector<Noise2D> noise2DS = {};

    /**
     * 二维噪音集类的构造方法
     * @param seed
     */
    explicit NoiseSet2D(double seed) {
        this->seed = seed;
    }

    /**
     * 添加一个噪音
     * @param diff 间距
     * @param loud 响度
     */
    void addNoise(int diff, double loud) {
        this->noise2DS.emplace_back(diff, loud, (int) (this->seed) + this->noise2DS.size() * 50);
    }

    // 获取该噪声处某一个位置的高度
    double getHeight(int x, int y) {
        double res = 0;
        for (Noise2D noise2D: this->noise2DS) {
            res += noise2D.getBuff(x, y);
        }
        return res;
    }
};

/**
 * 世界生成器类
 * 这个类里面的方法相当于一些涂鸦方法，给二维vector涂鸦东西
 */
class WorldGenerator {
    // 平滑函数
private:


public:
    /// 生成山
    static void mountain(vector<vector<GameObject>> &world) {
        NoiseSet2D m(uniform01());  // hash code from string todo
        m.addNoise(50, 20);
        m.addNoise(5, 25);
        m.addNoise(5, 5);
        for (int y = 0; y < world.size(); y++) {
            for (int x = 0; x < world[y].size(); x++) {
                if (m.getHeight(x, y) > 10) {
                    world[y][x] = stone;
                }
            }
        }
    }

    /// 生成矿石
    static void genOre(vector<vector<GameObject>> &world) {
        // 铁矿  // todo
        NoiseSet2D ironNoise(uniform01());
        ironNoise.addNoise(5, 20);
        ironNoise.addNoise(5, 25);
        ironNoise.addNoise(5, 5);
        NoiseSet2D coalNoise(uniform01());
        coalNoise.addNoise(5, 20);
        coalNoise.addNoise(5, 25);
        coalNoise.addNoise(5, 5);
        NoiseSet2D goldNoise(uniform01());
        goldNoise.addNoise(5, 10);
        goldNoise.addNoise(2, 10);
        goldNoise.addNoise(3, 10);
        NoiseSet2D diamondsNoise(uniform01());
        diamondsNoise.addNoise(5, 10);
        diamondsNoise.addNoise(2, 10);
        diamondsNoise.addNoise(3, 10);
        for (int y = 0; y < world.size(); y++) {
            for (int x = 0; x < world[y].size(); x++) {

                if (world[y][x] == stone && diamondsNoise.getHeight(x, y) > 10) {
                    world[y][x] = diamondBlock;
                }
                if (world[y][x] == stone && goldNoise.getHeight(x, y) > 10) {
                    world[y][x] = goldBlock;
                }
                if (world[y][x] == stone && coalNoise.getHeight(x, y) > 10) {
                    world[y][x] = coalBlock;
                }
                if (world[y][x] == stone && ironNoise.getHeight(x, y) > 10) {
                    world[y][x] = ironBlock;
                }

            }
        }
    }

    /// 生成小水坑
    static void pool(vector<vector<GameObject>> &world) {
        for (auto &y: world) {
            for (auto &x: y) {
                if (x == air && percentage(5)) {
                    x = water;
                }
            }
        }
    }

    /// 生长树木
    static void planTree(vector<vector<GameObject>> &world) {
        for (int y = 0; y < world.size(); y++) {
            for (int x = 0; x < world[y].size(); x++) {
                if (world[y][x] == air && percentage(5)) {
                    world[y][x] = wood;
                    // 同时生长树叶
                    int r = randint(3) + 1;  // 123
                    for (int leaveY = max(0, y - r); leaveY <= min((int) world.size() - 1, y + r); leaveY++) {
                        for (int leaveX = max(0, x - r); leaveX <= min((int) world[y].size() - 1, x + r); leaveX++) {
                            if (world[leaveY][leaveX] == air) {
                                world[leaveY][leaveX] = leave;
                            }
                        }
                    }
                }
            }
        }
    }
};

#endif //C__LEARN_WORLDGENERATOR_H
