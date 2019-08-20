#include "utils.h"

void logBin(char* p, int size){
    int i = 0;
    for (i = 0; i < size; i++) {
        printf("%c", *(p+i));
    }
}
