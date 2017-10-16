#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string.h>
#include <sys/time.h>
#include <vector>

using namespace std;

int cmp_str(string a, string b) {
    if (a.length() > b.length())
        return 1;
    else if (a.length() < b.length())
        return -1;
    else
        return a.compare(b);
}

string num2str(int i) {
    stringstream ss;
    ss << i;
    return ss.str();
}

void get_lines(int n, vector<string> &input_n,
               string path = "../input/input_string.txt") {
    ifstream input(path);
    input_n.push_back(" ");
    string current;
    for (int i = 0; i < n; i++) {
        getline(input, current);
        input_n.push_back(current);
    }
    input.close();
}
void insertion_sort(int n, string path = "../input/input_string.txt") {
    vector<string> input_n;
    get_lines(n, input_n, path);
    struct timeval start;
    gettimeofday(&start, NULL);
    for (int i = 2; i < n + 1; i++) {
        string key = input_n.at(i);
        int j = i - 1;
        while (j > 0 && (cmp_str(input_n.at(j), key) > 0)) {
            input_n.at(j + 1) = input_n.at(j);
            j -= 1;
        }
        input_n.at(j + 1) = key;
    }
    struct timeval end;
    gettimeofday(&end, NULL);
    long term =
        (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    ofstream result("../output/insertion_sort/result_" + num2str(int(log2(n))) +
                    ".txt");
    ofstream durtime("../output/insertion_sort/time.txt", ios::app);
    durtime << term << endl;
    for (int i = 1; i < n + 1; i++) {
        result << input_n.at(i) << endl;
    }
    result.close();
    durtime.close();
}

int left(int i) { return 2 * i; }
int right(int i) { return 2 * i + 1; }
int parent(int i) { return i / 2; }
void max_heapify(vector<string> &input_n, int i, int heapsize_minus = 0) {
    int l = left(i);
    int r = right(i);
    int largest;
    int heapsize = input_n.size() - 1 - heapsize_minus;
    if ((l <= heapsize) && (cmp_str(input_n.at(l), input_n.at(i)) > 0))
        largest = l;
    else
        largest = i;
    if ((r <= heapsize) && (cmp_str(input_n.at(r), input_n.at(largest)) > 0))
        largest = r;
    if (largest != i) {
        swap(input_n.at(i), input_n.at(largest));
        max_heapify(input_n, largest, heapsize_minus);
    }
}

void build_max_heap(vector<string> &input_n, int n) {
    for (int i = n / 2; i > 0; i--)
        max_heapify(input_n, i);
}

void heap_sort(int n, string path = "../input/input_string.txt") {
    vector<string> input_n;
    get_lines(n, input_n, path);
    struct timeval start;
    gettimeofday(&start, NULL);
    build_max_heap(input_n, n);

    for (int i = n, size = 1; i > 1; i--, size++) {
        swap(input_n.at(1), input_n.at(i));
        max_heapify(input_n, 1, size);
    }
    struct timeval end;
    gettimeofday(&end, NULL);
    long term =
        (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    ofstream result("../output/heap_sort/result_" + num2str(int(log2(n))) +
                    ".txt");
    ofstream durtime("../output/heap_sort/time.txt", ios::app);
    durtime << term << endl;
    for (int i = 1; i < n + 1; i++) {
        result << input_n.at(i) << endl;
    }
    result.close();
    durtime.close();
}

int partion(vector<string> &input_n, int p, int r) {
    string x = input_n.at(r);
    int i = p - 1;
    for (int j = p; j <= r - 1; j++) {
        if (cmp_str(input_n.at(j), x) <= 0) {
            i++;
            swap(input_n.at(i), input_n.at(j));
        }
    }
    swap(input_n.at(i + 1), input_n.at(r));
    return i + 1;
}

void quicksort(vector<string> &input_n, int p, int r) {
    if (p < r) {
        int q = partion(input_n, p, r);
        quicksort(input_n, p, q - 1);
        quicksort(input_n, q + 1, r);
    }
}

void quick_sort(int n, string path = "../input/input_string.txt") {
    vector<string> input_n;
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

void merge(vector<string> &input_n, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    string L[n1 + 2];
    string R[n2 + 2];
    int i, j;
    for (i = 1; i <= n1; i++)
        L[i] = input_n.at(p + i - 1);
    for (j = 1; j <= n2; j++)
        R[j] = input_n.at(q + j);
    L[n1 + 1] = R[n2 + 1] = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
    i = j = 1;
    for (int k = p; k <= r; k++) {
        if (cmp_str(L[i], R[j]) <= 0) {
            input_n.at(k) = L[i];
            i++;
        } else {
            input_n.at(k) = R[j];
            j++;
        }
    }
}

void merge_sort_original(vector<string> &input_n, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        merge_sort_original(input_n, p, q);
        merge_sort_original(input_n, q + 1, r);
        merge(input_n, p, q, r);
    }
}

void merge_sort(int n, string path = "../input/input_string.txt") {
    vector<string> input_n;
    get_lines(n, input_n, path);
    struct timeval start;
    gettimeofday(&start, NULL);
    merge_sort_original(input_n, 1, n);
    struct timeval end;
    gettimeofday(&end, NULL);
    long term =
        (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    ofstream result("../output/merge_sort/result_" + num2str(int(log2(n))) +
                    ".txt");
    ofstream durtime("../output/merge_sort/time.txt", ios::app);
    durtime << term << endl;
    for (int i = 1; i < n + 1; i++) {
        result << input_n.at(i) << endl;
    }
    result.close();
    durtime.close();
}
