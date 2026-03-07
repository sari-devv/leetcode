#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int* arr, int* tmp, int size) {
    if (size == 1) {
        return;
    }

    /* Merge both halves. */
    int mid = size / 2;
    merge(arr, tmp, mid);
    merge(arr + mid, tmp, size - mid);

    /* Both halves are sorted, go over both with two pointers and merge them.
     * In order to do that we use the tmp array to store the two unmerged halves
     * and merge them into arr. */
    memcpy(tmp, arr, size * sizeof(int));

    int* firstArr = tmp;
    int* secondArr = tmp + mid;
    int firstIdx = 0;
    int secondIdx = 0;

    int mergedIdx = 0;

    while (firstIdx < mid && secondIdx < size - mid) {
        if (firstArr[firstIdx] < secondArr[secondIdx]) {
            arr[mergedIdx] = firstArr[firstIdx];
            firstIdx++;
        } else {
            arr[mergedIdx] = secondArr[secondIdx];
            secondIdx++;
        }

        mergedIdx++;
    }

    while (firstIdx < mid) {
        arr[mergedIdx] = firstArr[firstIdx];
        firstIdx++;
        mergedIdx++;
    }

    while (secondIdx < size - mid) {
        arr[mergedIdx] = secondArr[secondIdx];
        secondIdx++;
        mergedIdx++;
    }

    return;
}

void mergeSort(int* arr, int size) {
    if (size == 1) {
        return;
    }

    int* tmp = (int*)malloc(size * sizeof(int));
    if (tmp == NULL) {
        return;
    }

    merge(arr, tmp, size);

    free(tmp);

    return;
}

static void printArr(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d%s", arr[i], i < size - 1 ? ", " : "");
    }
    printf("]\n");
}

static int matchesExpected(int* arr, int* expected, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] != expected[i])
            return 0;
    }
    return 1;
}

static void runTest(const char* name, int* arr, int* expected, int size) {
    printf("%-30s input:    ", name);
    printArr(arr, size);
    mergeSort(arr, size);
    printf("%-30s expected: ", "");
    printArr(expected, size);
    printf("%-30s output:   ", "");
    printArr(arr, size);
    printf("%-30s %s\n\n", "",
           matchesExpected(arr, expected, size) ? "PASS" : "FAIL");
}

int main(void) {
    /* Already sorted */
    int t1[] = {1, 2, 3, 4, 5};
    int e1[] = {1, 2, 3, 4, 5};
    runTest("Already sorted", t1, e1, 5);

    /* Reverse sorted */
    int t2[] = {5, 4, 3, 2, 1};
    int e2[] = {1, 2, 3, 4, 5};
    runTest("Reverse sorted", t2, e2, 5);

    /* Single element */
    int t3[] = {42};
    int e3[] = {42};
    runTest("Single element", t3, e3, 1);

    /* Two elements */
    int t4[] = {9, 1};
    int e4[] = {1, 9};
    runTest("Two elements", t4, e4, 2);

    /* Duplicates */
    int t5[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int e5[] = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    runTest("Duplicates", t5, e5, 10);

    /* Negatives and positives */
    int t6[] = {-3, 7, -1, 0, 4, -9, 2};
    int e6[] = {-9, -3, -1, 0, 2, 4, 7};
    runTest("Negatives and positives", t6, e6, 7);

    /* All same */
    int t7[] = {7, 7, 7, 7};
    int e7[] = {7, 7, 7, 7};
    runTest("All same", t7, e7, 4);

    return 0;
}
