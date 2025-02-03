#include <stdio.h>
#include <utmp.h>
// #include <unistd.h>

char errPrintFileOpen[] = "file open err";
char errPrintFileRead[] = "file read err";
int exitErr = -1;

int main(){
    struct utmp usrRecord;
    unsigned long readNum;

    // 1. open file
    FILE * fd = fopen("/var/run/utmp", "r");
    if (fd == NULL){
        perror(errPrintFileOpen);
        return exitErr;
    }
    // 2. read
    while(1){
        readNum = fread(&usrRecord, sizeof(struct utmp), 1, fd);
        if (readNum != 0) {
            if (usrRecord.ut_type == USER_PROCESS){
                printf("%s %s %s %d\n", 
                        usrRecord.ut_user, usrRecord.ut_line, usrRecord.ut_host, usrRecord.ut_tv.tv_sec);
            }
        }
        else break;
    }

    return fclose(fd);
}