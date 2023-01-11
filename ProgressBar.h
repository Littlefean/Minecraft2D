//
// Created by 20281 on 2022/9/12.
//

#ifndef C__LEARN_PROGRESSBAR_H
#define C__LEARN_PROGRESSBAR_H


/**
 * ��������
 * ����Ѫ������ʳ�����ȵ�
 */
class ProgressBar {
public:
    double maxValue;
    double value;

    ProgressBar(double mv, double v);

    /**
     * ����������ֵ����
     * �ܹ���ֹ�ӱ��ˣ����ɸ����˵����
     * @param d
     */
    void change(double d);

    /**
     * ֱ���ý��������ֵ����
     * ���ڣ�Ѫ������
     */
    void setMax();

    /**
     * ��ǰ���ǲ������˵�״̬
     * @return
     */
    [[nodiscard]] bool isMax() const;
};


#endif //C__LEARN_PROGRESSBAR_H
