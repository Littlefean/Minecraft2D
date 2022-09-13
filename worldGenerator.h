//
// ����������
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
 * ƽ�����������޴��ļ��ڲ�ʹ��
 * @param xi
 * @return
 */
double smoothFunc(double xi) {
    return 3 * pow(xi, 2) - 2 * pow(xi, 3);
}

/**
 * ��ά������
 */
class Noise2D {
    int diff;  // ���
    double loud;  // ���
    int seed;

    /**
     * ����һ�����꣬���������������������ĸ���������Դͷλ��
     * @param x ����
     * @param y ����
     * @return �ĸ�Դͷλ����ɵ�vector
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
        // ���� ���� ���� ����
        res.emplace_back(xMin, yMax);
        res.emplace_back(xMax, yMax);
        res.emplace_back(xMin, yMin);
        res.emplace_back(xMax, yMin);
        return res;
    }

    /**
     * ��ȡһ��Դͷ������ֵ
     * @param x ����
     * @param y ����
     * @return ����ֵ
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
     * ��ά������Ĺ��췽��
     * @param diff ���
     * @param loud ���
     * @param seed ����
     */
    Noise2D(int diff, double loud, int seed) {  // todo seed type
        this->diff = diff;
        this->loud = loud;
        this->seed = seed;
    }

    /**
     * ��ȡĳ��λ���ϵ�buff
     * @param x ����
     * @param y ����
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
 * ��ά��������
 */
class NoiseSet2D {

public:
    double seed;
    // �����ά�����������е����ά����
    vector<Noise2D> noise2DS = {};

    /**
     * ��ά��������Ĺ��췽��
     * @param seed
     */
    explicit NoiseSet2D(double seed) {
        this->seed = seed;
    }

    /**
     * ���һ������
     * @param diff ���
     * @param loud ���
     */
    void addNoise(int diff, double loud) {
        this->noise2DS.emplace_back(diff, loud, (int) (this->seed) + this->noise2DS.size() * 50);
    }

    // ��ȡ��������ĳһ��λ�õĸ߶�
    double getHeight(int x, int y) {
        double res = 0;
        for (Noise2D noise2D: this->noise2DS) {
            res += noise2D.getBuff(x, y);
        }
        return res;
    }
};

/**
 * ������������
 * ���������ķ����൱��һЩͿѻ����������άvectorͿѻ����
 */
class WorldGenerator {
    // ƽ������
private:


public:
    /// ����ɽ
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

    /// ���ɿ�ʯ
    static void genOre(vector<vector<GameObject>> &world) {
        // ����  // todo
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

    /// ����Сˮ��
    static void pool(vector<vector<GameObject>> &world) {
        for (auto &y: world) {
            for (auto &x: y) {
                if (x == air && percentage(5)) {
                    x = water;
                }
            }
        }
    }

    /// ������ľ
    static void planTree(vector<vector<GameObject>> &world) {
        for (int y = 0; y < world.size(); y++) {
            for (int x = 0; x < world[y].size(); x++) {
                if (world[y][x] == air && percentage(5)) {
                    world[y][x] = wood;
                    // ͬʱ������Ҷ
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
