#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int factorial(int n) {
    if (n == 1) {
        return 1;
    }

    return n * factorial(n - 1);
}

void printPermutation(int* pPerm) {
    printf("[");
    for (int j = 0; j < 3; j++) {
        printf("%d, ", pPerm[j]);
    }
    printf("]\n");
}

bool permuteAux(int* nums, int numsSize, int** pPermutationsArray, int currIdx,
                bool* pUsed, int* pCurrPermutation, int* pCurrPermutationIdx) {
    if (currIdx == numsSize) {
        printPermutation(pCurrPermutation);

        int* pPerm = (int*)malloc(sizeof(int) * numsSize);
        if (pPerm == NULL) {
            return false;
        }
        memcpy(pPerm, pCurrPermutation, sizeof(int) * numsSize);
        pPermutationsArray[*pCurrPermutationIdx] = pPerm;
        (*pCurrPermutationIdx)++;
        return true;
    }

    for (int i = 0; i < numsSize; i++) {
        if (pUsed[i] == true) {
            continue;
        }
        pUsed[i] = true;
        pCurrPermutation[currIdx] = nums[i];

        if (!permuteAux(nums, numsSize, pPermutationsArray, currIdx + 1, pUsed,
                        pCurrPermutation, pCurrPermutationIdx)) {
            return false;
        }

        pUsed[i] = false;
    }
    return true;
}

int** permute(int* nums, int numsSize, int* returnSize,
              int** returnColumnSizes) {
    int** pPermutationsArray = NULL;
    (*returnColumnSizes) = NULL;
    int* pCurrPermutation = NULL;
    bool* pUsed = NULL;

    int numPermutations = factorial(numsSize);
    *returnSize = numPermutations;
    pPermutationsArray = (int**)malloc(numPermutations * sizeof(int*));
    if (pPermutationsArray == NULL) {
        goto cleanup;
    }

    *returnColumnSizes = (int*)malloc(sizeof(int) * numPermutations);
    if (*returnColumnSizes == NULL) {
        goto cleanup;
    }

    int i;
    for (i = 0; i < numPermutations; i++) {
        (*returnColumnSizes)[i] = numsSize;
    }

    pCurrPermutation = (int*)malloc(sizeof(int) * numsSize);
    if (pCurrPermutation == NULL) {
        goto cleanup;
    }
    pUsed = (bool*)malloc(sizeof(int) * numsSize);
    if (pUsed == NULL) {
        goto cleanup;
    }
    for (i = 0; i < numsSize; i++) {
        pUsed[i] = false;
    }

    int currPermutationIdx = 0;
    bool ok = permuteAux(nums, numsSize, pPermutationsArray, 0, pUsed,
                         pCurrPermutation, &currPermutationIdx);

    free(pCurrPermutation);
    free(pUsed);

    if (!ok) {
        for (int i = 0; i < currPermutationIdx; i++) {
            free(pPermutationsArray[i]);
        }
        goto cleanup;
    }

    return pPermutationsArray;

cleanup:
    free(pPermutationsArray);
    free(*returnColumnSizes);
    free(pCurrPermutation);
    free(pUsed);

    return NULL;
}

int main() {
    int arr[3] = {1, 2, 3};
    int returnSize;
    int* returnColumnSizes;
    int** res;

    res = permute(arr, 3, &returnSize, &returnColumnSizes);
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < 3; j++) {
            printf("%d, ", res[i][j]);
        }
        printf("]\n");
    }

    free(returnColumnSizes);
    free(res);

    return 0;
}
