/* who1.c - a first version of the who program
 *          open, read UTMP file, and show results
 */

#include <stdio.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <stdlib.h>

void show_info(struct utmp *);
#define SHOWHOST

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
    printf("%-8.8s ", utmpbufp->ut_user);
    printf("%-8.8s ", utmpbufp->ut_line);
    printf("%10d ", utmpbufp->ut_tv.tv_sec);
# ifdef SHOWHOST
    printf("%s", utmpbufp->ut_host);
# endif
    putchar('\n');
}