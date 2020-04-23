#include "stdio.h"

unsigned int time33(char *);
int main(){
    char str[] = "1";
    int res;
    
    res = time33(str);
    printf("%d\n", res % (1024 ^ 2));
}

unsigned int time33(char *str){
    unsigned int hash = 5381;
    while(*str){
        hash += (hash << 5 ) + (*str++);
    }
    return (hash & 0x7FFFFFFF);
}