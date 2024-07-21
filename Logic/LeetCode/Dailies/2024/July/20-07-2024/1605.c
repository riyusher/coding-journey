/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** restoreMatrix(int* rowSum, int rowSumSize, int* colSum, int colSumSize, int* returnSize, int** returnColumnSizes) {
    int** result = (int**)malloc(rowSumSize * sizeof(int*));
    for (int i = 0; i < rowSumSize; i++) {
        result[i] = (int*)malloc(colSumSize * sizeof(int));
    }

    *returnSize = rowSumSize;
    *returnColumnSizes = (int*)malloc(rowSumSize * sizeof(int));
    for (int i = 0; i < rowSumSize; i++) {
        (*returnColumnSizes)[i] = colSumSize;
    }

    for (int i = 0; i < rowSumSize; i++) {
        for (int j = 0; j < colSumSize; j++) {
            int value = (rowSum[i] < colSum[j]) ? rowSum[i] : colSum[j];
            result[i][j] = value;
            rowSum[i] -= value;
            colSum[j] -= value;
        }
    }

    return result;
}