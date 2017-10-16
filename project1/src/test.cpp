#include <fstream>
#include <iostream>
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

void test(vector<string> &h) {
    cout << h.at(0) << endl;
    h.at(1) = "hdjsahdk";
}

int main() {

    cout << string(100) << endl;
    return 0;
}
