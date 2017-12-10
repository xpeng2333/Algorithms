#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <vector>

using namespace std;

vector<string> output; //保存所有括号化方案

// int转string
string int2str(int i) {
    stringstream ss;
    ss << i;
    return ss.str();
}
//自底向上表格法
void MatrixChainOrder(int *p, int (*m)[32], int (*s)[32], int length) {
    int n = length - 1;
    for (int i = 1; i < length; i++) {
        m[i][i] = 0;
    }
    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}
//输出规划结果
void PRINTOPTIMALPARENS(int (*s)[32], int i, int j) {
    if (i == j) {
        cout << "A" << i;
        output.push_back("A");
        output.push_back(int2str(i)); //将i转为string
    } else {
        cout << "(";
        output.push_back("(");
        PRINTOPTIMALPARENS(s, i, s[i][j]);
        PRINTOPTIMALPARENS(s, s[i][j] + 1, j);
        cout << ")";
        output.push_back(")");
    }
}

int main() {
    //生成输入文件
    ofstream input("../input/input.txt");
    for (long i = 0; i < 31; i++)
        input << 5000 + rand() % 20000 << endl;
    input.close();
    //不同的规模
    int nTable[4] = {5, 10, 20, 30};
    int m[32][32], s[32][32]; // m用来保存代价,s用来记录最优值m[i][j]的分割点k
    int p[32] = {0}; //存储矩阵链
    for (int i = 0; i < 4; i++) {
        int n = nTable[i] + 1;
        ifstream data("../input/input.txt");
        for (int j = 0; j < n; j++) {
            data >> p[j];
        }
        data.close();
        output.clear();
        ofstream result("../output/result.txt", ios::app);
        struct timeval start;
        struct timeval end;
        gettimeofday(&start, NULL);
        MatrixChainOrder(p, m, s, n);
        PRINTOPTIMALPARENS(s, 1, n - 1);
        gettimeofday(&end, NULL);
        result << "矩阵链<";
        for (int i = 1; i < n - 1; i++) {
            result << "A" << i << ",";
        }
        result << "A" << n - 1 << ">的结果为：";
        for (int i = 0; i < output.size(); i++)
            result << output.at(i);
        result << endl;
        result.close();
        cout << endl;
        cout << (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)
             << endl;
        ofstream timeResult("../output/time.txt", ios::app);
        timeResult << "规模为" << n - 1 << "时耗时:"
                   << (end.tv_sec - start.tv_sec) * 1000000 +
                          (end.tv_usec - start.tv_usec)
                   << "us" << endl;
        timeResult.close();
    }
    return 0;
}
