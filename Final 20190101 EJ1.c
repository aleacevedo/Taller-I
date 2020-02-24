#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getNewLen(char* str, int first, int last, int repeat) {
    return (strlen(str) + (last - first + 1) * (repeat - 1));
}

char* replicar(char* str, int first, int last, int repeat) {
    char* newStr = malloc(sizeof(char) * getNewLen(str, first, last, repeat));
    memcpy(newStr, str, first);
    for(int i = 0; i<repeat; i++) {
        int newPos = first + ((last - first + 1) * i);
        memcpy(newStr + newPos, str + first, last - first + 1);
    }
    int finalPos = first + ((last - first + 1) * repeat);
    memcpy(newStr + finalPos, str + last + 1, strlen(str) - last - 1);
    return newStr;
}



int main() {
    char myStr[] = "Hola";
    char *myRepStr = replicar(myStr, 1,2,3);
    free(myRepStr);
    return 0;
}
