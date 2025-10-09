#ifndef MY_LIB_H
#define MY_LIB_H

#include <stdio.h>
#include <stdlib.h>

#define BUFFER 31

typedef struct {
    char id[BUFFER];
    char part[BUFFER];
    char dest[BUFFER];
    char data[BUFFER];
    char ora_p[BUFFER];
    char ora_a[BUFFER];
    int ret;
} pullman;

// Prototipi delle funzioni per il merge sort
void merge_sort(pullman *vetp[], int n, int (*cmp)(const void *, const void *));
void merge_sort_rec(pullman *vetp[], pullman *temp[], int left, int right, int (*cmp)(const void *, const void *));
void merge(pullman *vetp[], pullman *temp[], int left, int mid, int right, int (*cmp)(const void *, const void *));

#endif // MY_LIB_H