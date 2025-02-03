// 功能：实现more（仅实现用法1：more filename）

#include <stdio.h>

#define PAGELEN 24
#define LINELEN 80

const char errPrintArgcNum[] = "arg num err";
char errPrintFileOpen[] = "file open err";
int exitErr = -1;

void do_more(FILE * fp);

int main(int argc, char * argv[]){
    // --1. 参数检查
    if (argc != 2){
        printf(errPrintArgcNum);
        // perror(errPrintArgcNum);  // 不能使用，因为perror函数会使用库中的全局变量errno表示什么错误发生，而这里的错误是自定义的，所以errno其实是没有错误
        //                              // 代码结果：arg num err: Success
        return exitErr;
    }
    // --2. 读取文件
    FILE * readF =  fopen(argv[1], "r");
    if (!readF){
        perror(errPrintFileOpen);
        return exitErr;
    }
    // // --3. 显示文件
    // int c;
    // while ((c = fgetc(readF)) != EOF){
    //     putchar(c);
    // }
    // --3. 显示文件
    do_more(readF);
    return fclose(readF); // 这里最好遵循谁开谁关，main开所以main关
}

// 为什么代码结构这么混乱！！！
void do_more(FILE * fp){
    int getLineLen = LINELEN + 1; // 因为函数fgets会在最后添加 字符串结尾 '\0'
    char line[getLineLen]; 
    char * ret;
    // 1. 最开始先显示一屏
    for (int i = 0; i < PAGELEN; i++) {
        // 如果文件某一行超过 LINELEN ，所以需要截断，这种情况line[LINELEN] == '\0'
        line[LINELEN] = 'a';
        ret = fgets(line, getLineLen, fp);
        if (ret == NULL){
            return;
        }
        printf("%s", line);
        if (line[LINELEN] == '\0'){
            putchar('\n');
        }
    }
    // 2. 等待输入，进行下一步操作
    for (char getC = getchar(); ; ) {
        switch (getC) {
            case ' ': // 再显示一屏
                    printf("get space\n");
                    return;
                    break;
            case '\n': // 显示一行
                    printf("get enter\n");
                    return;
                    break;
            case 'q':return;
        }
    }
}