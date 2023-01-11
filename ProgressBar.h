//
// Created by 20281 on 2022/9/12.
//

#ifndef C__LEARN_PROGRESSBAR_H
#define C__LEARN_PROGRESSBAR_H


/**
 * 进度条类
 * 用于血条，饱食度条等等
 */
class ProgressBar {
public:
    double maxValue;
    double value;

    ProgressBar(double mv, double v);

    /**
     * 进度条更改值操作
     * 能够防止加爆了，减成负数了等情况
     * @param d
     */
    void change(double d);

    /**
     * 直接让进度条里的值顶满
     * 用于：血条补满
     */
    void setMax();

    /**
     * 当前条是不是满了的状态
     * @return
     */
    [[nodiscard]] bool isMax() const;
};


#endif //C__LEARN_PROGRESSBAR_H
