#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <sys/time.h>
#include <vector>

using namespace std;

string num2str(int i) {
    stringstream ss;
    ss << i;
    return ss.str();
}

void get_lines(int n, vector<int> &input_n,
               string path = "../input/input_num.txt") {
    ifstream input(path);
    input_n.push_back(-1);
    int current;
    for (int i = 0; i < n; i++) {
        input >> current;
        input_n.push_back(current);
    }
    input.close();
}

int partion(vector<int> &input_n, int p, int r) {
    int x = input_n.at(r);
    int i = p - 1;
    for (int j = p; j <= r - 1; j++) {
        if (input_n.at(j) <= x) {
            i++;
            swap(input_n.at(i), input_n.at(j));
        }
    }
    swap(input_n.at(i + 1), input_n.at(r));
    return i + 1;
}

void quicksort(vector<int> &input_n, int p, int r) {
    if (p < r) {
        int q = partion(input_n, p, r);
        quicksort(input_n, p, q - 1);
        quicksort(input_n, q + 1, r);
    }
}

void quick_sort(int n, string path = "../input/input_num.txt") {
    vector<int> input_n;
    get_lines(n, input_n, path);
    struct timeval start;
    gettimeofday(&start, NULL);
    quicksort(input_n, 1, n);
    struct timeval end;
    gettimeofday(&end, NULL);
    long term =
        (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    ofstream result("../output/quick_sort/result_" + num2str(int(log2(n))) +
                    ".txt");
    ofstream durtime("../output/quick_sort/time.txt", ios::app);
    durtime << term << endl;
    for (int i = 1; i < n + 1; i++) {
        result << input_n.at(i) << endl;
    }
    result.close();
    durtime.close();
}

void bubble_sort(int n, string path = "../input/input_num.txt") {
    vector<int> input_n;
    get_lines(n, input_n, path);
    struct timeval start;
    gettimeofday(&start, NULL);
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n + 1 - i; j++) {
            if (input_n.at(j) > input_n.at(j + 1)) {
                swap(input_n.at(j), input_n.at(j + 1));
            }
        }
    }
    struct timeval end;
    gettimeofday(&end, NULL);
    long term =
        (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    ofstream result("../output/bubble_sort/result_" + num2str(int(log2(n))) +
                    ".txt");
    ofstream durtime("../output/bubble_sort/time.txt", ios::app);
    durtime << term << endl;
    for (int i = 1; i < n + 1; i++) {
        result << input_n.at(i) << endl;
    }
    result.close();
    durtime.close();
}

void counting_sort(int n, string path = "../input/input_num.txt") {
    vector<int> input_n;
    get_lines(n, input_n, path);
    struct timeval start;
    gettimeofday(&start, NULL);
    int c[65536] = {0};
    int b[n + 1] = {0};
    for (int j = 1; j <= n; j++) {
        c[input_n.at(j)] = c[input_n.at(j)] + 1;
    }
    for (int i = 1; i <= 65535; i++) {
        c[i] += c[i - 1];
    }
    for (int j = n; j >= 1; j--) {
        b[c[input_n.at(j)]] = input_n.at(j);
        c[input_n.at(j)] -= 1;
    }
    struct timeval end;
    gettimeofday(&end, NULL);
    long term =
        (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    ofstream result("../output/counting_sort/result_" + num2str(int(log2(n))) +
                    ".txt");
    ofstream durtime("../output/counting_sort/time.txt", ios::app);
    durtime << term << endl;
    for (int i = 1; i < n + 1; i++) {
        result << input_n.at(i) << endl;
    }
    result.close();
    durtime.close();
}

void countSort_radix(vector<int> &input_n, int exp) {
    int n = input_n.size() - 1;
    int output[n + 1]; // 存储"被排序数据"的临时数组
    int buckets[10] = {0};

    // 将数据出现的次数存储在buckets[]中
    for (int i = 1; i <= n; i++) {
        buckets[(input_n.at(i) / exp) % 10]++;
    }
    // 更改buckets[i]。目的是让更改后的buckets[i]的值，是该数据在output[]中的位置。
    for (int i = 1; i < 10; i++) {
        buckets[i] += buckets[i - 1];
    }
    // 将数据存储到临时数组output[]中
    for (int i = n; i > 0; i--) {
        output[buckets[(input_n.at(i) / exp) % 10]] = input_n.at(i);
        buckets[(input_n.at(i) / exp) % 10]--;
    }
    // 将排序好的数据赋值给a[]
    for (int i = 1; i <= n; i++) {
        input_n.at(i) = output[i];
    }
}
void radix_sort(int n, string path = "../input/input_num.txt") {
    vector<int> input_n;
    get_lines(n, input_n, path);
    struct timeval start;
    gettimeofday(&start, NULL);
    int max = 65535;
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort_radix(input_n, exp);
    }
    struct timeval end;
    gettimeofday(&end, NULL);
    long term =
        (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    ofstream result("../output/radix_sort/result_" + num2str(int(log2(n))) +
                    ".txt");
    ofstream durtime("../output/radix_sort/time.txt", ios::app);
    durtime << term << endl;
    for (int i = 1; i < n + 1; i++) {
        result << input_n.at(i) << endl;
    }
    result.close();
    durtime.close();
}
