//
// Created by 20281 on 2023/1/12.
//

#include "ProgressBar.h"


//using namespace std;

/**
 * 进度条类
 * 用于血条，饱食度条等等
 */

ProgressBar::ProgressBar(double mv, double v) {
    this->maxValue = mv;
    this->value = v;
}

/**
 * 进度条更改值操作
 * 能够防止加爆了，减成负数了等情况
 * @param d
 */
void ProgressBar::change(double d) {
    this->value += d;
    if (this->value > this->maxValue) {
        this->value = this->maxValue;
    }
    if (this->value < 0) {
        this->value = 0;
    }
}

/**
 * 直接让进度条里的值顶满
 * 用于：血条补满
 */
void ProgressBar::setMax() {
    this->value = this->maxValue;
}

/**
 * 当前条是不是满了的状态
 * @return
 */
bool ProgressBar::isMax() const {
    return this->value >= this->maxValue;
}
