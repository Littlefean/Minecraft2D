//
// Created by 20281 on 2022/9/12.
//

#ifndef C__LEARN_PROGRESSBAR_H
#define C__LEARN_PROGRESSBAR_H

using namespace std;

/**
 * ��������
 * ����Ѫ������ʳ�����ȵ�
 */
class ProgressBar {
public:
    double maxValue;
    double value;

    ProgressBar(double mv, double v) {
        this->maxValue = mv;
        this->value = v;
    }

    /**
     * ����������ֵ����
     * �ܹ���ֹ�ӱ��ˣ����ɸ����˵����
     * @param d
     */
    void change(double d) {
        this->value += d;
        if (this->value > this->maxValue) {
            this->value = this->maxValue;
        }
        if (this->value < 0) {
            this->value = 0;
        }
    }

    /**
     * ֱ���ý��������ֵ����
     * ���ڣ�Ѫ������
     */
    void setMax() {
        this->value = this->maxValue;
    }

    /**
     * ��ǰ���ǲ������˵�״̬
     * @return
     */
    bool isMax() {
        return this->value >= this->maxValue;
    }
};


#endif //C__LEARN_PROGRESSBAR_H
