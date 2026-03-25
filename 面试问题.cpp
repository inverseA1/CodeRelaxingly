/*
同学面试遇到的算法题：坐标系中给定一个点P(x,y)，以及一个矩形，矩形有如下参数：
- 中心点坐标Q(X,Y)
- 长a，宽b
- 角度theta（这里我定义为矩形水平中心线相对于水平线绕中心点逆时针旋转的角度，范围在0 ~ 180）
问题是判断点在不在矩形中。
思路是通过矩阵变换将矩形变成水平矩形，然后判断曼哈顿距离
*/
#include <cmath>
#include <vector>
using namespace std;

class SOLUTION {
    public:
        bool IORectangle(POINT P, RECTANGLE R){
            this->Orthogonalization(P, R);
            if(abs(P.x - R.X) <= R.length / 2 && abs(P.y - R.Y) <= R.width/2){
                return true;
            }else{
                return false;
            }
        }
    void Orthogonalization(POINT& Point, RECTANGLE& Rectangle){
        vector<vector<double>> rmat = this->Rotationmatrix(- Rectangle.theta);
        this->MatTimesVec22(rmat, Point.x, Point.y);
        this->MatTimesVec22(rmat, Rectangle.X, Rectangle.Y);
    }
    vector<vector<double>> Rotationmatrix(double theta){
        vector<vector<double>> rmat = 
        {
            { cos(theta), -sin(theta) } ,
            { sin(theta),  cos(theta) }
        };
        return rmat;
    }
    void MatTimesVec22(vector<vector<double>> rmat, double& x, double& y){
        vector<double> point = { x, y };
        x = rmat[0][0] * point[0] + rmat[0][1] * point[1];
        y = rmat[1][0] * point[0] + rmat[1][1] * point[1];
    }
};

class RECTANGLE {
    public:
        double X;
        double Y;
        double length;
        double width;
        double theta;
};

class POINT{
    public:
        double x;
        double y;
};