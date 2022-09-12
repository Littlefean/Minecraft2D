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
    sapling = 266, // Ê÷Ãç
    barrier = 0,
};

unordered_map<GameObject, string> objectToStr{
        make_pair(air, "  "),
        make_pair(stone, "Ê¯"),
        make_pair(water, "Ë®"),
        make_pair(grass, "²Ý"),
        make_pair(leave, "Ò¶"),
        make_pair(dirt, "Äà"),
        make_pair(wood, "Ê÷"),
        make_pair(sapling, "Ãç"),
        make_pair(apple, "¹û"),
        make_pair(barrier, "X "),
};

bool isBlockCanThrough(GameObject o) {
    if (o == air || o == water || o == grass || o == sapling || o == apple || o == leave) {
        return true;
    } else {
        return false;
    }
}

bool isBlockCanPickUp(GameObject o) {
    if (o == sapling || o == apple) {
        return true;
    }
    return false;
}

bool isBlockCanDig(GameObject o) {
    if (o == grass || o == wood) {
        return true;
    } else {
        return false;
    }
}

// ÓÒ¼üÐ§¹û
bool isBlockPut(GameObject o) {
    if (o == wood || o == dirt || o == sapling || o == stone) {
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
