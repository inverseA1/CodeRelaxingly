#include <iostream>
#include <iomanip>
#include <string>
#include "InterviewProblem.hpp"

// 辅助函数：角度转弧度
double deg2rad(double deg) {
    return deg * PI / 180.0;
}

struct TestCase {
    std::string name;
    POINT point;
    RECTANGLE rect;   // rect.theta 应为弧度
    bool expected;
};

void runTest(const TestCase& test) {
    SOLUTION sol;
    bool result = sol.IORectangle(test.point, test.rect);

    std::cout << "Test: " << test.name << "\n";
    std::cout << "  Point (" << test.point.x << ", " << test.point.y << ")\n";
    std::cout << "  Rect: center(" << test.rect.X << ", " << test.rect.Y << "), size("
              << test.rect.length << ", " << test.rect.width << "), angle "
              << (test.rect.theta * 180.0 / PI) << " deg\n";
    std::cout << "  Expected: " << (test.expected ? "Inside" : "Outside")
              << ", Got: " << (result ? "Inside" : "Outside") << "\n";
    std::cout << (result == test.expected ? "  PASS\n" : "  FAIL\n");
    std::cout << "----------------------------------------\n";
}

int main() {
    // 测试用例（矩形角度以度为单位，内部转为弧度）
    runTest({
        "Inside, no rotation",
        POINT(2, 3),
        RECTANGLE(0, 0, 10, 8, deg2rad(0)),
        true
    });

    runTest({
        "Outside, no rotation",
        POINT(6, 5),
        RECTANGLE(0, 0, 10, 8, deg2rad(0)),
        false
    });

    runTest({
        "Inside, 45 deg rotation",
        POINT(1, 1),
        RECTANGLE(0, 0, 2*std::sqrt(2), 2*std::sqrt(2), deg2rad(45)),
        true
    });

    runTest({
        "Outside, 45 deg rotation",
        POINT(1.5, 1.5),
        RECTANGLE(0, 0, 2*std::sqrt(2), 2*std::sqrt(2), deg2rad(45)),
        false
    });

    runTest({
        "Inside, offset center, 30 deg",
        POINT(3, 4),
        RECTANGLE(2, 2, 4, 2, deg2rad(30)),
        false   // 数学验证为外部
    });

    runTest({
        "Outside, offset center, 30 deg",
        POINT(5, 5),
        RECTANGLE(2, 2, 4, 2, deg2rad(30)),
        false
    });

    runTest({
        "On boundary (top edge), no rotation",
        POINT(0, 4),
        RECTANGLE(0, 0, 10, 8, deg2rad(0)),
        true
    });

    runTest({
        "Inside, asymmetric, 60 deg",
        POINT(2.5, 1.8),
        RECTANGLE(0, 0, 6, 2, deg2rad(60)),
        false   // 数学验证为外部
    });

    runTest({
        "Outside, asymmetric, 60 deg",
        POINT(3.5, 2),
        RECTANGLE(0, 0, 6, 2, deg2rad(60)),
        false
    });

    runTest({
        "Inside, angle near 180 deg",
        POINT(1, 0),
        RECTANGLE(0, 0, 4, 2, deg2rad(179)),
        true
    });

    return 0;
}