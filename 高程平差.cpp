#include<iostream>
#include<Eigen/Dense> // ����Eigen�⣬�������Դ�������
#include<iomanip> // ���ڸ�ʽ�����

using namespace std;
using namespace Eigen;

int main() {
    // �۲�߲�
    VectorXf L(5);
    L << 5.835, 3.782, 9.64, 7.384, 2.27;

    // ����d
    VectorXf d(5);
    d << -237.483, 0, -237.483, 0, -237.483;

    // �����ĺ�l
    VectorXf l = -(d - L);

    // ������ϵ��
    MatrixXf B(5, 3);
    B << 1, 0, 0,
        -1, 1, 0,
         0, 1, 0,
         0, 1, -1,
         0, 0, 1;

    // Ȩ��(���۲�ֵ�໥����)
    MatrixXf P(5, 5);
    P << 2.9, 0, 0, 0, 0,
         0, 3.7, 0, 0, 0,
         0, 0, 2.5, 0, 0,
         0, 0, 0, 3.3, 0,
         0, 0, 0, 0, 4.0;

    // ����X�̲߳���
    cout << "����X�̲߳���" << endl;
    VectorXf X = (B.transpose() * P * B).inverse() * B.transpose() * P * l;   
    for (int i = 0; i < X.size(); ++i) {
        cout << char(66 + i) << "��߳�Ϊ��"<< X(i) << "m" << endl;
    }

    // ����۲�߲�ĸ���ֵv
    cout << endl;
    cout << "����۲�߲�ĸ���ֵv" << endl;
    VectorXf V = ((B * X - l) * 1000).array();
    for (int i = 0; i < V.size(); ++i) {
        cout << "�۲�߲�L" << i + 1 << "�ĸ���ֵv" << i + 1 << "��"<< V(i) << "mm" << endl;
    }

    // ���㵥λȨ�����
    cout << endl;
    cout << "���㵥λȨ�����" << endl;
    VectorXf n = (V.array() * V.array() * P.diagonal().array()).matrix();
    /*
    P.diagonal() ���ؾ��� P �ĶԽ���Ԫ����ɵ�������������һ�����������������������˾��� P �Խ����ϵ�Ԫ�ء�
    Ȼ��array() ���������������ת��Ϊһ�� Eigen ����,matrix()������������תΪ����
    */
    float m = sqrt(n.sum() / (5 - 3));      //n��������v��t��δ֪��x��(n-t)
    cout << "��λȨ�����Ϊ��" << m << "mm" << endl;

    return 0;
}
