#include <limits.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* luckyNumbers (int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    int* arrMin = (int*)malloc(sizeof(int) * matrixSize);
    int* arrMax = (int*)malloc(sizeof(int) * (*matrixColSize));

    for (int i = 0; i < matrixSize; i++) {
        int auxMin = INT_MAX;
        for (int j = 0; j < (*matrixColSize); j++) {
            if (matrix[i][j] < auxMin) {
                auxMin = matrix[i][j];
            }
        }
        arrMin[i] = auxMin;
    }

    for (int j = 0; j < (*matrixColSize); j++) {
        int auxMax = INT_MIN;
        for (int i = 0; i < matrixSize; i++) {
            if (matrix[i][j] > auxMax) {
                auxMax = matrix[i][j];
            }
        }
        arrMax[j] = auxMax;
    }
    
    int* result = (int*)malloc(sizeof(int) * (matrixSize));
    int resultI = 0;

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < (*matrixColSize); j++) {
            if (matrix[i][j] == arrMin[i] && matrix[i][j] == arrMax[j]) {
                result[resultI++] = matrix[i][j];
            }
        }

    }

    result = (int*)realloc(result, sizeof(int) * resultI);
    free(arrMin);
    free(arrMax);
    *returnSize = resultI;
    return result;
}