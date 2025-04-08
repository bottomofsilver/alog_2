#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 计算编辑距离的函数
int editDistance(const string& A, const string& B) {
    int m = A.size();
    int n = B.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // 初始化 dp 表
    for (int i = 0; i <= m; ++i) {
        dp[i][0] = i; // A 转为空字符串需要删除 i 次
    }
    for (int j = 0; j <= n; ++j) {
        dp[0][j] = j; // 空字符串转为 B 需要插入 j 次
    }

    // 填充 dp 表
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; // 字符相等，无需操作
            } else {
                dp[i][j] = min({dp[i - 1][j] + 1,    // 删除
                                dp[i][j - 1] + 1,    // 插入
                                dp[i - 1][j - 1] + 1 // 替换
                               });
            }
        }
    }

    return dp[m][n];
}

int main() {
    // 打开输入文件
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "无法打开输入文件 input.txt" << endl;
        return 1;
    }

    string A, B;
    getline(inputFile, A); // 读取字符串 A
    getline(inputFile, B); // 读取字符串 B
    inputFile.close();

    // 计算编辑距离
    int distance = editDistance(A, B);

    // 将结果写入输出文件
    ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        cerr << "无法打开输出文件 output.txt" << endl;
        return 1;
    }
    outputFile << distance << endl;
    outputFile.close();

    return 0;
}