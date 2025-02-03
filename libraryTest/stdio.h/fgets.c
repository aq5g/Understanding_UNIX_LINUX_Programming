#include <stdio.h>

# define LINELEN 128
// 1
// 2
// 3
// 4
// 5
// 6
// 7
// 8
// 9
// 10
int main(){
    FILE * fp = fopen("./fgets.c", "r");
    if (fp == NULL){
        perror("open file err:");
        return -1;
    }
    char line[LINELEN+1];
    char * ret = fgets(line, LINELEN+1, fp);
    fclose(fp);
    if (ret == NULL){
        perror("read file err:");
        return -1;
    }
    printf("%s", line);
    return 0;
}