#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void get_lines(int n, vector<int> &input_n, string path = "./input_num.txt") {
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

void quick_sort(int n, string path = "./input_num.txt") {
    vector<int> input_n;
    get_lines(n, input_n, path);
    quicksort(input_n, 1, n);
    for (int i = 1; i < n + 1; i++) {
        cout << input_n.at(i) << endl;
    }
}

int main() {
    quick_sort(100);
    return 0;
}