//
// Created by 20281 on 2022/9/12.
//
#ifndef C__LEARN_OBJECT_H
#define C__LEARN_OBJECT_H
#include <string>
#include <unordered_map>
using namespace std;
/**
 * ��Ʒö��
 * ö�ٵ�ֵ���ն˴�ӡ����ɫֵ
 * 0~256 һ����ѭ��
 * ö��ֵ�в������ظ���ţ������ظ�����ɫҪ��+256
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
    sapling = 10 + 256, // ����
    board = 6 + 256,
    stick = 6 + 256 * 2,
    workbench = 96, // ����̨
    // ����
    woodDraft = 6 + 256 * 3,
    stoneDraft = 8,
    ironDraft = 7 + 256,
    diamondDraft = 11,

    // ����
    skeleton = 8 + 256,
    sheep = 6 + 256 * 4,

    ironBlock = 135,
    coalBlock = 128,
    goldBlock = 142,
    diamondBlock = 139,
    brokenStone = 135 + 256,
};

/**
 * ��Ʒ��Ӧ��ӡ�ڿ���̨�ϵ��ַ�
 *
 */
unordered_map <GameObject, string> objectToStr{
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
        {workbench,    "̨"},
        {ironBlock,    "��"},
        {coalBlock,    "ú"},
        {goldBlock,    "��"},
        {diamondBlock, "��"},
        {woodDraft,    "��"},
        {stoneDraft,   "��"},
        {ironDraft,    "��"},
        {diamondDraft, "��"},

        {sheep,        "��"},
        {skeleton,     "��"},
};
// ����ÿ����Ʒ�ĺϳ�;����Ψһ��
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
 * ����ͨ���ϳɻ�õ�����
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
        {woodDraft,    1},
        {stoneDraft,   2},
        {ironDraft,    3},
        {diamondDraft, 4},
};

/**
 * ʳ�ﱥʳ�ȱ�
 */
unordered_map<GameObject, int> foodTastiness{
        {apple, 3},
};





/**
 * ��������Ƿ��ǿ��Ա���ҡ�������·������
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
 * ��Ʒ�Ƿ��ǿ��Լ�������
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
 * һ����Ʒ�Ƿ��ǿ����ھ��
 * ��Ӳ�ȱ������Ʒ���ǿ����ھ��
 * @param o ��Ʒ
 * @return �Ƿ�
 */
bool isBlockCanDig(GameObject o) {
    return BlockHardnessTable.find(o) != BlockHardnessTable.end();
}

/**
 * ����Ʒ�������ϵ�ʱ���Ƿ���Է��ó�ȥ
 * @param o ��Ʒ
 * @return �Ƿ�
 */
bool isBlockPut(GameObject o) {
    if (o == wood || o == dirt || o == sapling || o == stone) {
        return true;
    }
    return false;
}

/**
 * ��������Ƿ���Ա����ø��ǣ����������Ͽ��Է��ö���
 * �ƻ��ݷ�����Ҳ���Է��ö�����ֱ�ӰѲݷ����������
 * @param o ����
 * @return �Ƿ�
 */
bool isBlockBeCover(GameObject o) {
    if (o == air) {
        return true;
    }
    return false;
}


/**
 * һ����Ʒ�Ƿ��ܹ�����ҳ�
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
