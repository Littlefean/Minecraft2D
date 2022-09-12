//
// Created by 20281 on 2022/9/12.
//
#ifndef C__LEARN_OBJECT_H
#define C__LEARN_OBJECT_H

#include <string>
#include <unordered_map>

using namespace std;

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
    sapling = 266, // 树苗
    board = 262,
    stick = 518,
    workbench = 96, // 工作台
    woodDraft = 774, // 木稿子
    stoneDraft = 7 + 256,
    ironDraft = 7 + 256 * 2,
    diamondDraft = 7 + 256 * 3,
    ironBlock = 135,
    coalBlock = 128,
    goldBlock = 142,
    diamondBlock = 139,
    brokenStone = 391,
};

unordered_map<GameObject, string> objectToStr{
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
        {workbench,    "╤╤"},
        {ironBlock,    "^v"},
        {coalBlock,    "%%"},
        {goldBlock,    "*."},
        {diamondBlock, "<>"},
        {woodDraft,    "稿"},
        {stoneDraft,   "稿"},
        {ironDraft,    "稿"},
        {diamondDraft, "稿"},
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
        {woodDraft, 1},
        {stoneDraft, 2},
        {ironDraft, 3},
        {diamondDraft, 4},
};

// 左键效果
bool isBlockCanDig(GameObject o) {
    return BlockHardnessTable.find(o) != BlockHardnessTable.end();
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

namespace Recipe {
    unordered_map<GameObject, int> boardRecipe{
            make_pair(wood, 1),
    };
    unordered_map<GameObject, int> workbenchRecipe{
            make_pair(board, 4),
    };
    unordered_map<GameObject, int> stickRecipe{
            make_pair(board, 2),
    };
    unordered_map<GameObject, int> woodDraftRecipe{
            make_pair(board, 3),
            make_pair(stick, 2),
    };

}
using namespace Recipe;
unordered_map<GameObject, pair<unordered_map<GameObject, int>, int>> RecipeTable{
        make_pair(board, make_pair(boardRecipe, 4)),
        make_pair(workbench, make_pair(workbenchRecipe, 1)),
        make_pair(stick, make_pair(stickRecipe, 4)),
        make_pair(woodDraft, make_pair(woodDraftRecipe, 1)),
};


#endif //C__LEARN_OBJECT_H
