#include <fstream>
#include <iostream>
#include <math.h>
#include <string.h>
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

void get_lines(long n, vector<string> &input_n,
               string path = "./input_string.txt") {
    ifstream input(path);
    input_n.push_back(" ");
    string current;
    for (long i = 0; i < n; i++) {
        getline(input, current);
        input_n.push_back(current);
    }
    input.close();
}
void insertion_sort(long n, string path = "./input_string.txt") {
    vector<string> input_n;
    get_lines(n, input_n, path);
    for (long i = 2; i < n + 1; i++) {
        string key = input_n.at(i);
        long j = i - 1;
        while (j > 0 && (cmp_str(input_n.at(j), key) > 0)) {
            input_n.at(j + 1) = input_n.at(j);
            j -= 1;
        }
        input_n.at(j + 1) = key;
    }
    for (long i = 1; i < n + 1; i++) {
        cout << input_n.at(i) << endl;
    }
}

long left(long i) { return 2 * i; }
long right(long i) { return 2 * i + 1; }
long parent(long i) { return i / 2; }
void max_heapify(vector<string> &input_n, long i, long heapsize_minus = 0) {
    long l = left(i);
    long r = right(i);
    long largest;
    long heapsize = input_n.size() - 1 - heapsize_minus;
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

void build_max_heap(vector<string> &input_n, long n) {
    for (long i = n / 2; i > 0; i--)
        max_heapify(input_n, i);
}

void heap_sort(long n, string path = "./input_string.txt") {
    vector<string> input_n;
    get_lines(n, input_n, path);
    build_max_heap(input_n, n);

    for (long i = n, size = 1; i > 1; i--, size++) {
        swap(input_n.at(1), input_n.at(i));
        max_heapify(input_n, 1, size);
    }
    for (long i = 1; i < n + 1; i++) {
        cout << input_n.at(i) << endl;
    }
}

long partion(vector<string> &input_n, long p, long r) {
    string x = input_n.at(r);
    long i = p - 1;
    for (long j = p; j <= r - 1; j++) {
        if (cmp_str(input_n.at(j), x) <= 0) {
            i++;
            swap(input_n.at(i), input_n.at(j));
        }
    }
    swap(input_n.at(i + 1), input_n.at(r));
    return i + 1;
}

void quicksort(vector<string> &input_n, long p, long r) {
    if (p < r) {
        long q = partion(input_n, p, r);
        quicksort(input_n, p, q - 1);
        quicksort(input_n, q + 1, r);
    }
}

void quick_sort(long n, string path = "./input_string.txt") {
    vector<string> input_n;
    get_lines(n, input_n, path);
    quicksort(input_n, 1, n);
    for (long i = 1; i < n + 1; i++) {
        cout << input_n.at(i) << endl;
    }
}

void merge(vector<string> &input_n, long p, long q, long r) {
    long n1 = q - p + 1;
    long n2 = r - q;
    string L[n1 + 2];
    string R[n2 + 2];
    long i, j;
    for (i = 1; i <= n1; i++)
        L[i] = input_n.at(p + i - 1);
    for (j = 1; j <= n2; j++)
        R[j] = input_n.at(q + j);
    L[n1 + 1] = R[n2 + 1] = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
    i = j = 1;
    for (long k = p; k <= r; k++) {
        if (cmp_str(L[i], R[j]) <= 0) {
            input_n.at(k) = L[i];
            i++;
        } else {
            input_n.at(k) = R[j];
            j++;
        }
    }
}

void merge_sort_original(vector<string> &input_n, long p, long r) {
    if (p < r) {
        long q = (p + r) / 2;
        merge_sort_original(input_n, p, q);
        merge_sort_original(input_n, q + 1, r);
        merge(input_n, p, q, r);
    }
}

void merge_sort(long n, string path = "./input_string.txt") {
    vector<string> input_n;
    get_lines(n, input_n, path);
    merge_sort_original(input_n, 1, n);
    for (long i = 1; i < n + 1; i++) {
        cout << input_n.at(i) << endl;
    }
}
