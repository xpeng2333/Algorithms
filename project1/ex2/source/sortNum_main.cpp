#include "sortNum.h"
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int N[6] = {2, 5, 8, 11, 14, 17};
    for (int i = 0; i < 6; i++) {
        bubble_sort(pow(2, N[i]));
        quick_sort(pow(2, N[i]));
        radix_sort(pow(2, N[i]));
        counting_sort(pow(2, N[i]));
    }
    return 0;
}