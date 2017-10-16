#ifndef SORTNUM_H
#define SORTNUM_H

#include <iostream>
#include <string.h>
void quick_sort(int n, std::string path = "../input/input_num.txt");
void bubble_sort(int n, std::string path = "../input/input_num.txt");
void counting_sort(int n, std::string path = "../input/input_num.txt");
void radix_sort(int n, std::string path = "../input/input_num.txt");

#endif