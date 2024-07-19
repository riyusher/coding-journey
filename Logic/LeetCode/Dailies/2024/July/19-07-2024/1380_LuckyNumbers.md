# Lucky Numbers in a Matrix
### Date: 19-07-2024

## Intuition
The problem requires finding numbers in a given matrix that are both the minimum element in their respective row and the maximum element in their respective column. These numbers are termed "lucky numbers".

## Approach

1. **Find Elements:**
    - Create two arrays: `arrMin` to store the minimum of each row and `arrMax` to store the maximum of each column. Their sizes should be the number of rows and columns of the matrix, respectively.

    - Iterate over the matrix twice: first to fill `arrMin` and then to fill `arrMax`.
        - For `arrMin`, initialize an auxiliary variable `auxMin` to the maximum integer value (`INT_MAX`). Update `auxMin` while iterating through each row and assign the final value to `arrMin[i]`.

        - For `arrMax`, initialize an auxiliary variable `auxMax` to the minimum integer value (`INT_MIN`). Update `auxMax` while iterating through each column and assign the final value to `arrMax[j]`.

2. **Find the Lucky Numbers:**
    - Create a list `result` to store numbers that meet the conditions, and an index `resultI` to keep track of the number of lucky numbers found and as length the result list.

    - Iterate over the matrix. For each element, check if it is the minimum in its row (`arrMin[i]`) and the maximum in its column (`arrMax[j]`). If it meets both conditions, add it to `result`.
    
3. **Return Result:**
    - Reallocate `result` to fit the exact number of lucky numbers found and return it.

## Complexity

### Time Complexity

**O(n * m)**

- where `n` is the number of rows and `m` is the number of columns. This is because each element of the matrix is visited three times: once for finding row minimums, once for finding column maximums, and once for verifying the lucky numbers.

### Space Complexity

**O(n + m)**

- where `n` is the number of rows and `m` is the number of columns. This accounts for the space needed to store the row minimums (`arrMin`) and column maximums (`arrMax`).


## Code
```c
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
```

### References
- **[LeetCode Problem Link](https://leetcode.com/problems/lucky-numbers-in-a-matrix/?envType=daily-question&envId=2024-07-19)**
- **[Solution Code](Logic\LeetCode\Dailies\2024\July\19-07-2024\1380_LuckyNumbers.c)**