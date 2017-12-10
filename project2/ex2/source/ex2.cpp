#include <cmath>
#include <complex>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sys/time.h>
#include <vector>

const double PI = 3.14159265358979323846;
typedef std::complex<double> comDouble;

using namespace std;

vector<comDouble> RECURSIVEFFT(vector<comDouble> a, double flag = 1) {
    int n = (int)a.size();
    if (n == 1)
        return a;
    comDouble wn = comDouble(cos(2 * PI / n * flag), sin(2 * PI / n * flag));
    comDouble w = comDouble(1, 0);
    vector<comDouble> a0, a1;
    for (int i = 0; i < n; i++) {
        if (i & 1) {
            a1.push_back(a[i]);
        } else {
            a0.push_back(a[i]);
        }
    }
    vector<comDouble> y0 = RECURSIVEFFT(a0, flag);
    vector<comDouble> y1 = RECURSIVEFFT(a1, flag);
    vector<comDouble> y;
    y.resize(n);
    for (int k = 0; k <= n / 2 - 1; k++) {
        y[k] = y0[k] + w * y1[k];
        y[k + n / 2] = y0[k] - w * y1[k];
        w = w * wn;
    }
    return y;
}

//生成随机实数-50.0~50.0
double randRealnum() {
    struct timeval start;
    gettimeofday(&start, NULL);
    return rand() % 100 - 50 + start.tv_usec / (10000.0 * (rand() % 100 + 1));
}

void PolynMul(int n) {
    double A[n];
    double B[n];
    double Result[2 * n] = {0.0};
    ifstream input("../input/input.txt");
    for (int i = 0; i < n; i++) {
        input >> A[i];
    }
    for (int i = 0; i < n; i++) {
        input >> B[i];
    }
    input.close();
    struct timeval start;
    gettimeofday(&start, NULL);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Result[i + j] += A[i] * B[j];
        }
    }
    struct timeval end;
    gettimeofday(&end, NULL);
    ofstream output("../output/result.txt", ios::app);
    output << n << " "
           << "normal:" << endl;
    output << "   A:";
    for (int i = 0; i < n; i++)
        output << A[i] << " ";
    output << endl;
    output << "   B:";
    for (int i = 0; i < n; i++)
        output << B[i] << " ";
    output << endl;
    output << "   Result:";
    for (int i = 0; i < 2 * n; i++) {
        output << Result[i] << " ";
    }
    output << endl;
    output.close();
    ofstream outime("../output/time.txt", ios::app);
    outime << n << " normal "
           << (end.tv_sec - start.tv_sec) * 1000000 +
                  (end.tv_usec - start.tv_usec)
           << " us" << endl;
    outime.close();
}

void RecuFFT(int n) {
    ifstream input("../input/input.txt");
    vector<comDouble> A, B;

    for (int i = 0; i < n; i++) {
        double temp;
        input >> temp;
        A.push_back(comDouble(temp, 0));
    }
    for (int i = 0; i < n; i++) {
        double temp;
        input >> temp;
        B.push_back(comDouble(temp, 0));
    }
    input.close();
    ofstream output("../output/result.txt", ios::app);
    output << n << " FFT:" << endl;
    output << "   A:";
    for (int i = 0; i < n; i++) {
        output << A.at(i).real() << " ";
    }
    output << endl;
    output << "   B:";
    for (int i = 0; i < n; i++) {
        output << B.at(i).real() << " ";
    }
    output << endl;

    int NN = pow(2, 1 + ceil(log2(n)));
    for (int i = n; i < NN; i++) {
        A.push_back(comDouble(0, 0));
        B.push_back(comDouble(0, 0));
    }
    struct timeval start;
    gettimeofday(&start, NULL);
    vector<comDouble> A_FFT = RECURSIVEFFT(A, 1);
    vector<comDouble> B_FFT = RECURSIVEFFT(B, 1);
    vector<comDouble> C_FFT;
    C_FFT.resize(NN);
    for (int i = 0; i < NN; i++) {
        C_FFT[i] = A_FFT[i] * B_FFT[i];
    }
    vector<comDouble> result = RECURSIVEFFT(C_FFT, -1);
    struct timeval end;
    gettimeofday(&end, NULL);
    output << "   result:";
    for (int i = 0; i < 2 * n; i++) {
        output << result.at(i).real() / NN << " ";
    }
    output << endl;
    output.close();
    ofstream outime("../output/time.txt", ios::app);
    outime << n << " FFT "
           << (end.tv_sec - start.tv_sec) * 1000000 +
                  (end.tv_usec - start.tv_usec)
           << " us" << endl;
    outime.close();
}

int main() {
    //生成输入文件

    ofstream input("../input/input.txt");
    for (int i = 0; i < 120; i++) {
        input << randRealnum() << endl;
    }
    input.close();

    int nTable[4] = {4, 16, 32, 60};
    for (int i = 0; i < 4; i++) {
        PolynMul(nTable[i]);
        RecuFFT(nTable[i]);
    }
    return 0;
}
