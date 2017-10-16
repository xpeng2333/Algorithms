#include <fstream>
#include <iostream>
using namespace std;

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