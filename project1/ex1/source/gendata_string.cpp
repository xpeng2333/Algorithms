#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;

int main()
{
    ofstream input("./input_string.txt");
    long n = pow(2, 17);
    int c = -1;
    srand((unsigned)time(NULL));
    for (long j = 0; j < n; j++)
    {
        bool flag = false;
        for (long i = 0; i < 32; i++)
        {
            c = rand() % 27;
            if (c != 26)
                flag = true;
            if (c == 26 && flag)
                break;
            if (c != 26)
                input << char('a' + c);
        }
        input << endl;
    }
    input.close();
    return 0;
}