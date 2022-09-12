//
// Created by 20281 on 2022/9/12.
//
#ifndef C__LEARN_OBJECT_H
#define C__LEARN_OBJECT_H

#include <string>
#include <unordered_map>

using namespace std;

enum GameObject {
    air = 7,
    stone = 112,
    water = 17,
    grass = 10,
    leave = 2,
    dirt = 102,
    wood = 6,
    apple = 13,
    sapling = 266, // 树苗
    barrier = 0,
};

unordered_map<GameObject, string> objectToStr{
        make_pair(air, "  "),
        make_pair(stone, "  "),
        make_pair(water, "水"),
        make_pair(grass, "草"),
        make_pair(leave, "叶"),
        make_pair(dirt, "泥"),
        make_pair(wood, "木"),
        make_pair(sapling, "苗"),
        make_pair(apple, "果"),
        make_pair(barrier, "X "),
};

// 是否可穿过
bool isBlockCanThrough(GameObject o) {
    if (o == air || o == water || o == grass || o == sapling || o == apple || o == leave) {
        return true;
    } else {
        return false;
    }
}

// 是否可以拾起
bool isBlockCanPickUp(GameObject o) {
    if (o == sapling || o == apple) {
        return true;
    }
    return false;
}

// 左键效果
bool isBlockCanDig(GameObject o) {
    if (o == grass || o == wood) {
        return true;
    } else {
        return false;
    }
}

// 右键效果
bool isBlockPut(GameObject o) {
    if (o == wood || o == dirt || o == sapling || o == stone) {
        return true;
    }
    return false;
}

// 这个方块是否可以被放置覆盖
bool isBlockBeCover(GameObject o) {
    if (o == air) {
        return true;
    }
    return false;
}

unordered_map<GameObject, int> foodTastiness{
        make_pair(apple, 3),
};

bool isEatable(GameObject o) {
    if (foodTastiness.contains(o)) {
        return true;
    }
    return false;
}


#endif //C__LEARN_OBJECT_H
