#include <stdlib.h>

char * mergeAlternately(char * word1, char * word2) {
    int word1Len = strlen(word1);
    int word2Len = strlen(word2);
    int resultLength = word1Len + word2Len;

    char* result = (char*)malloc(sizeof(char) * (resultLength + 1));
    if (result == NULL) {
        return NULL;
    }

    int word1I = 0, word2I = 0, resultI = 0;

    while (word1I < word1Len && word2I < word2Len) {
        result[resultI++] = word1[word1I++];
        result[resultI++] = word2[word2I++];
    }

    while (word1I < word1Len) {
        result[resultI++] = word1[word1I++];
    }

    while (word2I < word2Len) {
        result[resultI++] = word2[word2I++];
    }
    
    result[resultI] = '\0';

    return result;
}