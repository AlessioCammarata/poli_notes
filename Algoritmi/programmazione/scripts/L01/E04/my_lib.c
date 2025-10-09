#include "my_lib.h"

void merge(pullman *vetp[], pullman *temp[], int left, int mid, int right, int (*cmp)(const void *, const void *)) {
    int i = left, j = mid, k = left;
    while (i < mid && j < right) {
        if (cmp(vetp[i], vetp[j]) <= 0) {
            temp[k++] = vetp[i++];
        } else {
            temp[k++] = vetp[j++];
        }
    }
    while (i < mid) temp[k++] = vetp[i++];
    while (j < right) temp[k++] = vetp[j++];
    for (i = left; i < right; i++) vetp[i] = temp[i];
}

void merge_sort_rec(pullman *vetp[], pullman *temp[], int left, int right, int (*cmp)(const void *, const void *)) {
    if (right - left > 1) {
        int mid = (left + right) / 2;
        merge_sort_rec(vetp, temp, left, mid, cmp);
        merge_sort_rec(vetp, temp, mid, right, cmp);
        merge(vetp, temp, left, mid, right, cmp);
    }
}

void merge_sort(pullman *vetp[], int n, int (*cmp)(const void *, const void *)) {
    pullman **temp = malloc(n * sizeof(pullman*));
    if (!temp) {
        printf("Errore di allocazione memoria per merge sort\n");
        return;
    }
    merge_sort_rec(vetp, temp, 0, n, cmp);
    free(temp);
}