#ifndef SORTSTR_H
#define SORTSTR_h

#include <iostream>
#include <string.h>

void merge_sort(long n, std::string path = "./input_string.txt");
void quick_sort(long n, std::string path = "./input_string.txt");
void heap_sort(long n, std::string path = "./input_string.txt");
void insertion_sort(long n, std::string path = "./input_string.txt");

#endif