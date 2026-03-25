#ifndef POINT_RECT_HPP
#define POINT_RECT_HPP

#include <cmath>
#include <vector>

const double PI = std::acos(-1.0);

struct POINT {
    double x, y;
    POINT(double x = 0, double y = 0) : x(x), y(y) {}
};

struct RECTANGLE {
    double X, Y;      // 中心坐标
    double length;    // 长（水平方向）
    double width;     // 宽（垂直方向）
    double theta;     // 旋转角度（弧度）

    RECTANGLE(double X = 0, double Y = 0, double l = 0, double w = 0, double theta_rad = 0)
        : X(X), Y(Y), length(l), width(w), theta(theta_rad) {}
};

class SOLUTION {
public:
    // 判断点是否在矩形内（矩形theta为弧度）
    bool IORectangle(const POINT& P, const RECTANGLE& R) const {
        // 将点转换到矩形局部坐标系（矩形回正后）
        double dx = P.x - R.X;
        double dy = P.y - R.Y;

        double cosTheta = std::cos(R.theta);
        double sinTheta = std::sin(R.theta);
        double localX =  cosTheta * dx + sinTheta * dy;
        double localY = -sinTheta * dx + cosTheta * dy;

        double eps = 1e-9;
        return std::abs(localX) <= R.length / 2 + eps &&
               std::abs(localY) <= R.width / 2 + eps;
    }
};

#endif // POINT_RECT_HPP