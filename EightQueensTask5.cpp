/**
 * 任务5：图形界面实现
 * 八皇后问题 - EasyX图形界面版
 * 
 * 功能：
 * - EasyX图形库基础用法
 * - 棋盘绘制
 * - 圆形皇后绘制
 * - 数据可视化
 * 
 * 编译说明（Visual Studio）：
 * 1. 下载安装 EasyX: https://easyx.cn/
 * 2. 在VS中创建项目，包含此文件
 * 3. 确保项目属性中配置了EasyX的include和lib路径
 * 
 * 命令行编译（需配置好VS环境变量）：
 * cl /EHsc EightQueensTask5.cpp user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /I C:\EasyX\include /link /LIBPATH:C:\EasyX\lib
 */

#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <vector>
using namespace std;

const int N = 8;
const int BLOCK_SIZE = 60;           // 每个格子的大小
const int BOARD_SIZE = N * BLOCK_SIZE;  // 棋盘总尺寸
const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 700;

// 颜色定义
const int COLOR_BOARD_LIGHT = RGB(240, 240, 240);   // 浅色格子
const int COLOR_BOARD_DARK = RGB(180, 180, 180);    // 深色格子
const int COLOR_QUEEN = RED;                         // 皇后颜色（红色）
const int COLOR_BOARD_LINE = RGB(80, 80, 80);       // 棋盘线条
const int COLOR_BG = WHITE;                          // 背景色

class QueenSolver {
private:
    int n;
    vector<int> queen;
    vector<vector<int>> solutions;
    bool* colUsed;
    bool* diag1Used;
    bool* diag2Used;

public:
    QueenSolver(int size = N) : n(size) {
        queen.resize(n, -1);
        colUsed = new bool[n];
        diag1Used = new bool[2 * n - 1];
        diag2Used = new bool[2 * n - 1];
    }
    
    ~QueenSolver() {
        delete[] colUsed;
        delete[] diag1Used;
        delete[] diag2Used;
    }
    
    void init() {
        fill(queen.begin(), queen.end(), -1);
        fill(colUsed, colUsed + n, false);
        fill(diag1Used, diag1Used + 2 * n - 1, false);
        fill(diag2Used, diag2Used + 2 * n - 1, false);
        solutions.clear();
    }
    
    bool isSafe(int row, int col) {
        return !colUsed[col] && 
               !diag1Used[row - col + n - 1] && 
               !diag2Used[row + col];
    }
    
    void place(int row, int col) {
        queen[row] = col;
        colUsed[col] = true;
        diag1Used[row - col + n - 1] = true;
        diag2Used[row + col] = true;
    }
    
    void remove(int row, int col) {
        queen[row] = -1;
        colUsed[col] = false;
        diag1Used[row - col + n - 1] = false;
        diag2Used[row + col] = false;
    }
    
    // 求所有解并保存
    int solveAndSaveAll() {
        init();
        solveRecursive(0);
        return solutions.size();
    }
    
    vector<vector<int>>& getSolutions() {
        return solutions;
    }
    
    int getSolutionCount() const {
        return solutions.size();
    }
    
private:
    void solveRecursive(int row) {
        for (int col = 0; col < n; col++) {
            if (isSafe(row, col)) {
                place(row, col);
                
                if (row == n - 1) {
                    solutions.push_back(queen);
                } else {
                    solveRecursive(row + 1);
                }
                
                remove(row, col);
            }
        }
    }
};

class GraphicsBoard {
private:
    int solutionNum;
    int totalSolutions;

public:
    GraphicsBoard() : solutionNum(0), totalSolutions(0) {}
    
    void initGraph() {
        initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
        setbkcolor(COLOR_BG);
        cleardevice();
    }
    
    void closeGraph() {
        closegraph();
    }
    
    void setSolutionInfo(int current, int total) {
        solutionNum = current;
        totalSolutions = total;
    }
    
    // 绘制棋盘
    void drawBoard() {
        // 绘制格子
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                int x = col * BLOCK_SIZE;
                int y = row * BLOCK_SIZE;
                
                // 国际象棋配色
                if ((row + col) % 2 == 0) {
                    setfillcolor(COLOR_BOARD_LIGHT);
                } else {
                    setfillcolor(COLOR_BOARD_DARK);
                }
                
                // 填充格子
                solidrectangle(x, y, x + BLOCK_SIZE, y + BLOCK_SIZE);
            }
        }
        
        // 绘制边框
        setlinestyle(PS_SOLID, 3);
        setlinecolor(COLOR_BOARD_LINE);
        rectangle(0, 0, BOARD_SIZE, BOARD_SIZE);
        
        // 绘制内部分割线
        setlinestyle(PS_SOLID, 1);
        for (int i = 1; i < N; i++) {
            // 垂直线
            line(i * BLOCK_SIZE, 0, i * BLOCK_SIZE, BOARD_SIZE);
            // 水平线
            line(0, i * BLOCK_SIZE, BOARD_SIZE, i * BLOCK_SIZE);
        }
    }
    
    // 绘制皇后（红色圆形）
    void drawQueens(const vector<int>& queen) {
        for (int row = 0; row < N; row++) {
            int col = queen[row];
            int x = col * BLOCK_SIZE + BLOCK_SIZE / 2;
            int y = row * BLOCK_SIZE + BLOCK_SIZE / 2;
            int radius = BLOCK_SIZE / 2 - 10;
            
            // 绘制红色实心圆
            setfillcolor(COLOR_QUEEN);
            solidcircle(x, y, radius);
            
            // 绘制边框
            setlinecolor(DARKGRAY);
            setlinestyle(PS_SOLID, 2);
            circle(x, y, radius);
            
            // 在圆心绘制Q字母
            setbkmode(TRANSPARENT);
            setcolor(WHITE);
            settextstyle(20, 0, "Arial");
            char str[2] = "Q";
            outtextxy(x - 8, y - 12, str);
        }
    }
    
    // 显示信息
    void drawInfo() {
        // 右侧信息面板背景
        setfillcolor(RGB(245, 245, 245));
        solidrectangle(BOARD_SIZE + 10, 10, WINDOW_WIDTH - 10, 200);
        setlinecolor(RGB(200, 200, 200));
        rectangle(BOARD_SIZE + 10, 10, WINDOW_WIDTH - 10, 200);
        
        // 标题
        setbkcolor(RGB(245, 245, 245));
        setcolor(BLACK);
        settextstyle(24, 0, "Microsoft YaHei");
        outtextxy(BOARD_SIZE + 30, 30, "八皇后问题");
        
        // 当前解信息
        char buf[100];
        sprintf(buf, "第 %d / %d 个解", solutionNum, totalSolutions);
        settextstyle(18, 0, "Microsoft YaHei");
        outtextxy(BOARD_SIZE + 30, 80, buf);
        
        sprintf(buf, "共 %d 个解", totalSolutions);
        outtextxy(BOARD_SIZE + 30, 110, buf);
        
        // 提示信息
        setcolor(DARKGRAY);
        settextstyle(14, 0, "Microsoft YaHei");
        outtextxy(BOARD_SIZE + 30, 160, "← → 显示上一个/下一个");
        outtextxy(BOARD_SIZE + 30, 180, "ESC 退出程序");
    }
    
    // 显示操作提示
    void drawTips() {
        setfillcolor(RGB(245, 245, 245));
        solidrectangle(BOARD_SIZE + 10, WINDOW_HEIGHT - 100, WINDOW_WIDTH - 10, WINDOW_HEIGHT - 10);
        setlinecolor(RGB(200, 200, 200));
        rectangle(BOARD_SIZE + 10, WINDOW_HEIGHT - 100, WINDOW_WIDTH - 10, WINDOW_HEIGHT - 10);
        
        setbkcolor(RGB(245, 245, 245));
        setcolor(DARKGRAY);
        settextstyle(14, 0, "Microsoft YaHei");
        outtextxy(BOARD_SIZE + 30, WINDOW_HEIGHT - 85, "操作说明:");
        outtextxy(BOARD_SIZE + 30, WINDOW_HEIGHT - 65, "← 或 → : 浏览解");
        outtextxy(BOARD_SIZE + 30, WINDOW_HEIGHT - 45, "ESC : 退出");
    }
};

int main() {
    // 创建求解器和图形板
    QueenSolver solver(N);
    GraphicsBoard board;
    
    // 求解所有解
    cout << "正在求解八皇后问题的所有解..." << endl;
    int count = solver.solveAndSaveAll();
    cout << "共找到 " << count << " 个解。" << endl;
    
    if (count == 0) {
        cout << "无解！" << endl;
        return 0;
    }
    
    // 初始化图形窗口
    board.initGraph();
    
    bool running = true;
    int currentSolution = 0;
    vector<vector<int>>& solutions = solver.getSolutions();
    
    // 设置初始解信息
    board.setSolutionInfo(1, count);
    
    while (running) {
        // 清屏
        BeginBatchDraw();
        cleardevice();
        
        // 绘制
        board.drawBoard();
        board.drawQueens(solutions[currentSolution]);
        board.drawInfo();
        board.drawTips();
        
        FlushBatchDraw();
        
        // 获取按键
        char key = getch();
        
        if (key == 27) {  // ESC 退出
            running = false;
        } 
        else if (key == 0 || key == -32) {  // 方向键前缀
            key = getch();
            if (key == 75) {  // 左箭头 上一个
                currentSolution = (currentSolution - 1 + count) % count;
                board.setSolutionInfo(currentSolution + 1, count);
            } 
            else if (key == 77) {  // 右箭头 下一个
                currentSolution = (currentSolution + 1) % count;
                board.setSolutionInfo(currentSolution + 1, count);
            }
        }
        else if (key == ' ' || key == '\r') {  // 空格或回车 下一个
            currentSolution = (currentSolution + 1) % count;
            board.setSolutionInfo(currentSolution + 1, count);
        }
    }
    
    board.closeGraph();
    cout << "感谢使用！" << endl;
    return 0;
}