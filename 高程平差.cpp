#include<iostream>
#include<Eigen/Dense> // 导入Eigen库，用于线性代数运算
#include<iomanip> // 用于格式化输出

using namespace std;
using namespace Eigen;

int main() {
    // 观测高差
    VectorXf L(5);
    L << 5.835, 3.782, 9.64, 7.384, 2.27;

    // 常数d
    VectorXf d(5);
    d << -237.483, 0, -237.483, 0, -237.483;

    // 常数的和l
    VectorXf l = -(d - L);

    // 参数的系数
    MatrixXf B(5, 3);
    B << 1, 0, 0,
        -1, 1, 0,
         0, 1, 0,
         0, 1, -1,
         0, 0, 1;

    // 权重(各观测值相互独立)
    MatrixXf P(5, 5);
    P << 2.9, 0, 0, 0, 0,
         0, 3.7, 0, 0, 0,
         0, 0, 2.5, 0, 0,
         0, 0, 0, 3.3, 0,
         0, 0, 0, 0, 4.0;

    // 计算X高程参数
    cout << "计算X高程参数" << endl;
    VectorXf X = (B.transpose() * P * B).inverse() * B.transpose() * P * l;   
    for (int i = 0; i < X.size(); ++i) {
        cout << char(66 + i) << "点高程为："<< X(i) << "m" << endl;
    }

    // 计算观测高差的改正值v
    cout << endl;
    cout << "计算观测高差的改正值v" << endl;
    VectorXf V = ((B * X - l) * 1000).array();
    for (int i = 0; i < V.size(); ++i) {
        cout << "观测高差L" << i + 1 << "的改正值v" << i + 1 << "："<< V(i) << "mm" << endl;
    }

    // 计算单位权中误差
    cout << endl;
    cout << "计算单位权中误差" << endl;
    VectorXf n = (V.array() * V.array() * P.diagonal().array()).matrix();
    /*
    P.diagonal() 返回矩阵 P 的对角线元素组成的向量，即返回一个列向量，该列向量包含了矩阵 P 对角线上的元素。
    然后，array() 函数将这个列向量转换为一个 Eigen 数组,matrix()将向量或数组转为矩阵
    */
    float m = sqrt(n.sum() / (5 - 3));      //n个改正数v，t个未知数x。(n-t)
    cout << "单位权中误差为：" << m << "mm" << endl;

    return 0;
}
