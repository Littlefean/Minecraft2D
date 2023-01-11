//
// Created by 20281 on 2022/9/12.
//
#ifndef C__LEARN_OBJECT_H
#define C__LEARN_OBJECT_H
#include <string>
#include <unordered_map>
using namespace std;
/**
 * 物品枚举
 * 枚举的值是终端打印的颜色值
 * 0~256 一个大循环
 * 枚举值中不能有重复编号，所以重复的颜色要标+256
 */
enum GameObject {
    barrier = 0,
    air = 7,
    stone = 143,
    water = 17,
    grass = 10,
    leave = 2,
    dirt = 102,
    wood = 6,
    apple = 13,
    sapling = 10 + 256, // 树苗
    board = 6 + 256,
    stick = 6 + 256 * 2,
    workbench = 96, // 工作台
    // 稿子
    woodDraft = 6 + 256 * 3,
    stoneDraft = 8,
    ironDraft = 7 + 256,
    diamondDraft = 11,

    // 生物
    skeleton = 8 + 256,
    sheep = 6 + 256 * 4,

    ironBlock = 135,
    coalBlock = 128,
    goldBlock = 142,
    diamondBlock = 139,
    brokenStone = 135 + 256,
};

/**
 * 物品对应打印在控制台上的字符
 *
 */
unordered_map <GameObject, string> objectToStr{
        {barrier,      "X "},
        {brokenStone,  "╳╳"},
        {air,          "  "},
        {stone,        "  "},
        {water,        "水"},
        {grass,        "草"},
        {leave,        "叶"},
        {dirt,         "泥"},
        {wood,         "木"},
        {sapling,      "苗"},
        {apple,        "果"},
        {board,        "板"},
        {stick,        "棍"},
        {workbench,    "台"},
        {ironBlock,    "铁"},
        {coalBlock,    "煤"},
        {goldBlock,    "金"},
        {diamondBlock, "钻"},
        {woodDraft,    "稿"},
        {stoneDraft,   "稿"},
        {ironDraft,    "稿"},
        {diamondDraft, "稿"},

        {sheep,        "羊"},
        {skeleton,     "骷"},
};
// 假设每种物品的合成途径是唯一的
unordered_map <GameObject, unordered_map<GameObject, int>> RecipeTable{
        {board,        {{wood,         1},}},
        {stick,        {{board,        2},}},
        {workbench,    {{board,        4},}},
        {woodDraft,    {{board,        3}, {stick, 2},}},
        {stoneDraft,   {{stone,        3}, {stick, 2},}},
        {ironDraft,    {{ironBlock,    3}, {stick, 2},}},
        {diamondDraft, {{diamondBlock, 3}, {stick, 2},}},
};
/**
 * 可以通过合成获得的数量
 */
unordered_map<GameObject, int> GainCount{
        {board,        4},
        {stick,        4},
        {workbench,    1},
        {woodDraft,    1},
        {stoneDraft,   1},
        {ironDraft,    1},
        {diamondDraft, 1},
};
/**
 * 方块硬度表
 * 方块硬度  挖爆他的概率
 */
unordered_map<GameObject, double> BlockHardnessTable{
        {grass,        1},
        {wood,         0.5},
        {dirt,         0.7},
        {stone,        0.1},
        {coalBlock,    0.1},
        {ironBlock,    0.1},
        {goldBlock,    0.1},
        {diamondBlock, 0.1},
};
/**
 * 方块的挖掘等级限制
 * 左侧方块被破坏至少需要多少级的破坏力
 */
unordered_map<GameObject, int> BlockDigCondition{
        {grass,        0},
        {wood,         0},
        {dirt,         0},
        {stone,        1},
        {coalBlock,    2},
        {ironBlock,    2},
        {goldBlock,    3},
        {diamondBlock, 3},
};

/**
 * 工具附加挖掘等级
 *
 */
unordered_map<GameObject, int> ToolDigLevel{
        {woodDraft,    1},
        {stoneDraft,   2},
        {ironDraft,    3},
        {diamondDraft, 4},
};

/**
 * 食物饱食度表
 */
unordered_map<GameObject, int> foodTastiness{
        {apple, 3},
};





/**
 * 这个方块是否是可以被玩家、生物走路穿过的
 * @param o
 * @return
 */
bool isBlockCanThrough(GameObject o) {
    if (o == air || o == water || o == grass || o == sapling || o == apple || o == leave) {
        return true;
    } else {
        return false;
    }
}

/**
 * 物品是否是可以捡起来的
 * @param o
 * @return
 */
bool isBlockCanPickUp(GameObject o) {
    if (o == sapling || o == apple) {
        return true;
    }
    return false;
}


/**
 * 一个物品是否是可以挖掘的
 * 在硬度表里的物品都是可以挖掘的
 * @param o 物品
 * @return 是否
 */
bool isBlockCanDig(GameObject o) {
    return BlockHardnessTable.find(o) != BlockHardnessTable.end();
}

/**
 * 该物品拿在手上的时候是否可以放置出去
 * @param o 物品
 * @return 是否
 */
bool isBlockPut(GameObject o) {
    if (o == wood || o == dirt || o == sapling || o == stone) {
        return true;
    }
    return false;
}

/**
 * 这个方块是否可以被放置覆盖，空气方块上可以放置东西
 * 计划草方块上也可以放置东西，直接把草方块给覆盖了
 * @param o 方块
 * @return 是否
 */
bool isBlockBeCover(GameObject o) {
    if (o == air) {
        return true;
    }
    return false;
}


/**
 * 一个物品是否能够被玩家吃
 * @param o
 * @return
 */
bool isEatable(GameObject o) {
    if (foodTastiness.contains(o)) {
        return true;
    }
    return false;
}



#endif //C__LEARN_OBJECT_H
