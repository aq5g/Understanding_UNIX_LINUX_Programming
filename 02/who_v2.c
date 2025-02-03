/* who2.c - read utmp file and list info therein
 *        - suppresses empty records
 *        - formats time nicely
 */

#include <stdio.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

#define SHOWHOST

void showtime(long);
void show_info(struct utmp *);

int main(){
    struct utmp current_record;
    int utmpfd;
    int reclen = sizeof(current_record);

    if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1){
        perror(UTMP_FILE);
        exit(1);
    }

    while (read(utmpfd, &current_record, reclen) == reclen) 
        show_info(&current_record);

    return close(utmpfd);
}

void
show_info(struct utmp * utmpbufp)
/* displays contents of the utmp struct in human readable form
 * *note* these sizes should not be hardwired
*/
{
    if (utmpbufp->ut_type != USER_PROCESS) return;
    
    printf("%-8.8s ", utmpbufp->ut_user);
    printf("%-8.8s ", utmpbufp->ut_line);
    showtime(utmpbufp->ut_tv.tv_sec);
# ifdef SHOWHOST
    if (utmpbufp->ut_host[0] != '\0')
        printf("(%s)", utmpbufp->ut_host);
# endif
    putchar('\n');
}

void showtime(long timeval)
{
    struct tm *timeinfo = localtime(&timeval);
    char str[20];
    strftime(str, sizeof(str), "%Y-%m-%d %H:%M", timeinfo);
    printf("%16.16s", str);
}