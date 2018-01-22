#include <stdio.h>
#include <stdlib.h>

int partition(int *datas, int beg, int last, int mid);
int select(int *datas, int length, int i);
void swap(int *a, int *b);

int main() {
    int datas[12] = {32, 23, 12, 67, 45, 78, 10, 39, 9, 58, 125, 84};
    int i, ret;
    printf("The array is: \n");
    for (i = 0; i < 12; ++i)
        printf("%d ", datas[i]);
    printf("\n");
    /*
    for (i = 1; i <= 12; ++i) {
        ret = select(datas, 12, i);
        printf("The %dth least number is: %d \n", i, datas[i - 1]);
    }
    */
    printf("%d\n", select(datas, 12, 12));
    exit(0);
}

int partition(int *datas, int beg, int last, int mid) {
    int i, j;
    swap(datas + mid, datas + last);
    i = beg;
    for (j = beg; j < last; j++) {
        if (datas[j] < datas[last]) {
            swap(datas + i, datas + j);
            i++;
        }
    }
    swap(datas + i, datas + last);
    return i;
}

int select(int *datas, int length, int i) {
    int groups, pivot;
    int j, k, t, q, beg, glen;
    int mid;
    int temp, index;
    int *pmid;
    if (length == 1)
        return datas[length - 1];
    if (length % 5 == 0)
        groups = length / 5;
    else
        groups = length / 5 + 1;
    pmid = (int *)malloc(sizeof(int) * groups);
    index = 0;
    for (j = 0; j < groups; j++) {
        beg = j * 5;
        glen = beg + 5;
        for (t = beg + 1; t < glen && t < length; t++) {
            temp = datas[t];
            for (q = t - 1; q >= beg && datas[q] > datas[q + 1]; q--)
                swap(datas + q, datas + q + 1);
            swap(datas + q + 1, &temp);
        }
        glen = glen < length ? glen : length;
        pmid[index++] = beg + (glen - beg) / 2;
    }
    for (t = 1; t < groups; t++) {
        temp = pmid[t];
        for (q = t - 1; q >= 0 && datas[pmid[q]] > datas[pmid[q + 1]]; q--)
            swap(pmid + q, pmid + q + 1);
        swap(pmid + q + 1, &temp);
    }
    mid = pmid[groups / 2];
    pivot = partition(datas, 0, length - 1, mid);
    k = pivot + 1;
    if (k == i)
        return datas[pivot];
    else if (k < i)
        return select(datas + k, length - k, i - k);
    else
        return select(datas, pivot, i);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}