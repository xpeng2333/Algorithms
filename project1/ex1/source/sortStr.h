#ifndef SORTSTR_H
#define SORTSTR_H

#include <iostream>
#include <string.h>

void merge_sort(int n, std::string path = "../input/input_string.txt");
void quick_sort(int n, std::string path = "../input/input_string.txt");
void heap_sort(int n, std::string path = "../input/input_string.txt");
void insertion_sort(int n, std::string path = "../input/input_string.txt");

#endif