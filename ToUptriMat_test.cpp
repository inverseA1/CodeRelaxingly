// test_uptri_fixed.cpp
#include "LineralAlgebra.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <string>

// ---------- 辅助函数 ----------
bool IsRowEchelon(const matrix& mat, double eps = 1e-12) {
    int row = GetRow(mat);
    int col = GetCol(mat);
    int prev_pivot = -1;
    bool zero_row_seen = false;
    for (int i = 0; i < row; ++i) {
        int pivot = -1;
        for (int j = 0; j < col; ++j) {
            if (std::fabs(mat[i][j]) > eps) {
                pivot = j;
                break;
            }
        }
        if (pivot == -1) {
            zero_row_seen = true;
        } else {
            if (zero_row_seen) return false;       // 非零行不能出现在全零行下方
            if (pivot <= prev_pivot) return false; // 主元列必须严格递增
            prev_pivot = pivot;
        }
    }
    return true;
}

bool MatrixEqual(const matrix& A, const matrix& B, double eps = 1e-10) {
    if (GetRow(A) != GetRow(B) || GetCol(A) != GetCol(B)) return false;
    for (int i = 0; i < GetRow(A); ++i)
        for (int j = 0; j < GetCol(A); ++j)
            if (std::fabs(A[i][j] - B[i][j]) > eps)
                return false;
    return true;
}

// ---------- 测试主函数 ----------
int main() {
    int passed = 0, failed = 0;

    auto run_test = [&](const std::string& desc, matrix input, const matrix& expected) {
        matrix original = input;
        ToUptriMat(input);

        bool echelon_ok = IsRowEchelon(input);
        bool match_ok = MatrixEqual(input, expected);

        if (echelon_ok && match_ok) {
            std::cout << "[PASS] " << desc << std::endl;
            ++passed;
        } else {
            std::cout << "[FAIL] " << desc << std::endl;
            if (!echelon_ok) std::cout << "  -> 结果不是行阶梯形！" << std::endl;
            if (!match_ok)   std::cout << "  -> 与预期矩阵不符。" << std::endl;
            std::cout << "  输入矩阵：" << std::endl;
            PrintMat(original);
            std::cout << "  变换结果：" << std::endl;
            PrintMat(input);
            std::cout << "  预期结果：" << std::endl;
            PrintMat(expected);
            ++failed;
        }
    };

    // 1. 3x3 可逆方阵
    run_test("3x3 可逆方阵",
             {{2, 1, -1},
              {-3, -1, 2},
              {-2, 1, 2}},
             {{-3, -1, 2},               // 选主元 -3 换到第0行
              {0, 1.666666666666667, 0.666666666666667},   // 消元后第1行
              {0, 0, 0.2}});            // 最终右下角是 0.2

    // 2. 3x3 奇异矩阵
    run_test("3x3 奇异矩阵",
             {{1, 2, 3},
              {4, 8, 12},
              {7, 14, 21}},
             {{7, 14, 21},
              {0, 0, 0},
              {0, 0, 0}});

    // 3. 负数主元绝对值最大
    run_test("负数主元绝对值最大",
             {{1, 2, 3},
              {2, 5, 6},
              {-10, 1, 2}},
             {{-10, 1, 2},
              {0, 5.2, 6.4},
              {0, 0, 0.615384615384615}});  // 修正预期

    // 4. 行数 > 列数 (3x2)
    run_test("行数 > 列数 (3x2)",
             {{2, 3},
              {4, 5},
              {6, 7}},
             {{6, 7},
              {0, 0.666666666666667},
               {0, 0}});                 // 修正预期

    // 5. 行数 < 列数 (2x3)
    run_test("行数 < 列数 (2x3)",
             {{1, 2, 3},
              {4, 5, 6}},
             {{4, 5, 6},
              {0, 0.75, 1.5}});

    // 6. 已经是上三角
    run_test("已经是上三角",
             {{3, 1, 4},
              {0, 2, 5},
              {0, 0, 6}},
             {{3, 1, 4},
              {0, 2, 5},
              {0, 0, 6}});

    // 7. 首列全为零（修正算法会正确处理）
    run_test("首列全为零",
            {{0, 1, 2},
            {0, 3, 4},
            {0, 5, 6}},
            {{0, 5, 6},
            {0, 0, 0.8},
            {0, 0, 0}});

    // 8. 中间全零列
    run_test("中间全零列",
             {{1, 2, 3},
              {4, 8, 12},
              {7, 14, 22}},
             {{7, 14, 22},    // 消元后第二列从第1行往下全零（跳过），第三列主元在第1行，消元第2行
              {0, 0, -0.571428571428571},  // 约等于 -0.571428571428571
              {0, 0, 0}});

    // 9. 包含全零行
    run_test("包含全零行",
             {{1, 2, 3},
              {0, 0, 0},
              {4, 5, 6}},
             {{4, 5, 6},
              {0, 0.75, 1.5},
              {0, 0, 0}});

    // 10. 单行矩阵
    run_test("单行矩阵 (1x3)",
             {{2, 3, 4}},
             {{2, 3, 4}});

    // 11. 单列矩阵
    run_test("单列矩阵 (3x1)",
             {{2}, {4}, {6}},
             {{6}, {0}, {0}});

    // 12. 零矩阵
    run_test("零矩阵 (2x2)",
             {{0, 0}, {0, 0}},
             {{0, 0}, {0, 0}});

    // 13. 接近零的主元
    run_test("小主元视为零",
             {{1, 2}, {1e-13, 3}},
             {{1, 2}, {0, 3}});

    // 14. 复杂换行消元
    run_test("综合换行消元",
             {{0, 2, 0, 4},
              {3, 6, 9, 12},
              {1, 2, 3, 4},
              {0, 0, 5, 6}},
             {{3, 6, 9, 12},
              {0, 2, 0, 4},
              {0, 0, 5, 6},
              {0, 0, 0, 0}});

    std::cout << "\n===========================" << std::endl;
    std::cout << passed << " 通过, " << failed << " 失败。" << std::endl;
    return failed ? 1 : 0;
}