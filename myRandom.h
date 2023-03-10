// 随机函数工具库
// 此模块中含有全局随机引擎
// Created by 20281 on 2022/9/13.
//

#ifndef C__LEARN_MYRANDOM_H
#define C__LEARN_MYRANDOM_H

/**
 * 生成 [0, n) 范围的随机整数
 * @param n
 * @return
 */
int randint(int n);
/**
 * 百分之多少的事情发生一件事
 * @param n
 * @return
 */
bool percentage(int n);
/**
 * 返回0~1之间的随机小数
 * @return
 */
double uniform01();

// double randRate() {
//
// }

#endif //C__LEARN_MYRANDOM_H
