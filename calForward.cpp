#include <iostream>
#include <vector>
#include <iomanip> // 用于设置输出精度

using namespace std;

// 函数：生成能量图
vector<vector<double>> generateEnergyMap(const vector<vector<int>>& A) {
    int n = A.size();      // A的行数
    int m = A[0].size();   // A的列数
    vector<vector<double>> B(n, vector<double>(m, 0.0));  // 初始化B为全零矩阵
    
    // 能量传播的偏移位置，8个方向（上下左右和四个对角线）
    vector<pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},  // 上下左右
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}, // 四个对角线
        {-2,0},{2,0},{0,-2},{0,2}
    };
    
    // 遍历能量图A
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (A[i][j] == 1) {  // 如果当前位置是1
                // 为当前位置分配能量并向周围扩散
                B[i][j]+=0.311;
                for (const auto& dir : directions) {
                    int ni = i + dir.first;
                    int nj = j + dir.second;
                    
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m) {  // 判断新位置是否在边界内
                        if (dir.first == 0 || dir.second == 0) {  // 上下左右
                            if (abs(dir.first)==1 || abs(dir.second)==1){
                                B[ni][nj] += 0.125;
                            }
                            else if (abs(dir.first)==2 || abs(dir.second)==2){
                                B[ni][nj] += 0.05;
                            }
                        } else {  // 对角线
                            B[ni][nj] += 0.05;
                        }
                    }
                }
            }
        }
    }
    
    return B;
}

int main() {
    // 示例输入矩阵A
    vector<vector<int>> A = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };
    
    // 生成能量图B
    vector<vector<double>> B = generateEnergyMap(A);
    
    // 输出能量图B，保留三位小数
    for (const auto& row : B) {
        for (const auto& val : row) {
            cout << fixed << setprecision(3) << val << " "; // 保留三位小数
        }
        cout << endl;
    }
    
    return 0;
}