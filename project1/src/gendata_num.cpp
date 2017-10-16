#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;

int main()
{
    ofstream input("./input_num.txt");
    srand((unsigned)time(NULL));
    long n = pow(2, 17);
    for (long i = 0; i < n; i++)
        input << 1 + rand() % 65535 << endl;
    input.close();
    return 0;
}