#include <stdbool.h>

bool isSubsequence(char* s, char* t) {
    int sI = 0;

    for (int i = 0; i < strlen(t); i++) {
        if (t[i] == s[sI]) {
            sI++;
        }
    }

    return sI == strlen(s);
}