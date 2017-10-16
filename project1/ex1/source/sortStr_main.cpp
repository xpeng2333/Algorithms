#include "sortStr.h"
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int N[6] = {2, 5, 8, 11, 14, 17};
    for (int i = 0; i < 6; i++) {
        insertion_sort(pow(2, N[i]));
        heap_sort(pow(2, N[i]));
        merge_sort(pow(2, N[i]));
        quick_sort(pow(2, N[i]));
    }
    return 0;
}