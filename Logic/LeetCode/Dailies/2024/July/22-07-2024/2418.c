#include <limits.h>
    /**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** sortPeople(char** names, int namesSize, int* heights, int heightsSize, int* returnSize) {
    int heightCompared = INT_MAX;

    char** result = (char**)malloc(sizeof(char*) * namesSize);
    int resultIndex = 0;

    for (int i = 0; i < namesSize; i++) {
        int actualHeight = INT_MIN;
        int tallerIndex = -1;
        for (int j = 0; j < heightsSize; j++) {
            if (heights[j] > actualHeight && heights[j] < heightCompared) {
                actualHeight = heights[j];
                tallerIndex = j;
            }
        }
        heightCompared = actualHeight;
        
        result[resultIndex] = (char*)malloc(sizeof(char) * (strlen(names[tallerIndex]) + 1));
        strcpy(result[resultIndex++], names[tallerIndex]);
    }

    *returnSize = resultIndex;
    return result;
}