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
    sapling = 266, // ����
    board = 262,
    stick = 518,
    workbench = 96, // ����̨
    woodDraft = 774, // ľ����
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
        {brokenStone,  "�w�w"},
        {air,          "  "},
        {stone,        "  "},
        {water,        "ˮ"},
        {grass,        "��"},
        {leave,        "Ҷ"},
        {dirt,         "��"},
        {wood,         "ľ"},
        {sapling,      "��"},
        {apple,        "��"},
        {board,        "��"},
        {stick,        "��"},
        {workbench,    "�h�h"},
        {ironBlock,    "^v"},
        {coalBlock,    "%%"},
        {goldBlock,    "*."},
        {diamondBlock, "<>"},
        {woodDraft,    "��"},
        {stoneDraft,   "��"},
        {ironDraft,    "��"},
        {diamondDraft, "��"},
};

// �Ƿ�ɴ���
bool isBlockCanThrough(GameObject o) {
    if (o == air || o == water || o == grass || o == sapling || o == apple || o == leave) {
        return true;
    } else {
        return false;
    }
}

// �Ƿ����ʰ��
bool isBlockCanPickUp(GameObject o) {
    if (o == sapling || o == apple) {
        return true;
    }
    return false;
}

/**
 * ����Ӳ�ȱ�
 * ����Ӳ��  �ڱ����ĸ���
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
 * ������ھ�ȼ�����
 * ��෽�鱻�ƻ�������Ҫ���ټ����ƻ���
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
 * ���߸����ھ�ȼ�
 *
 */
unordered_map<GameObject, int> ToolDigLevel{
        {woodDraft, 1},
        {stoneDraft, 2},
        {ironDraft, 3},
        {diamondDraft, 4},
};

// ���Ч��
bool isBlockCanDig(GameObject o) {
    return BlockHardnessTable.find(o) != BlockHardnessTable.end();
}

// �Ҽ�Ч��
bool isBlockPut(GameObject o) {
    if (o == wood || o == dirt || o == sapling || o == stone) {
        return true;
    }
    return false;
}

// ��������Ƿ���Ա����ø���
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
