#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmpx.h>
#include <fcntl.h>
#include <time.h>

#include "utils.h"

void showtime(long);
void show_info(struct utmpx *);

int main(int argc, char const *argv[]) {
    struct utmpx utbuf;
    int utmpdf;

    // 打开文件
    if ((utmpdf = open(UTMPX_FILE, O_RDONLY)) == -1) {
        perror(UTMPX_FILE);
        exit(1);
    }

    // 读文件
    int size = 628;
    while (read(utmpdf, &utbuf, size) == size) {
        // printf("\nread a struct: size %d\n", size);
        show_info(&utbuf);
    }
    printf("\n");

    // 关闭
    close(utmpdf);

    // setutxent();
    // printf("正确显示：\n");
    // int i = 0;
    // while (1) {
    //     struct utmpx *user_info = getutxent();
    //     if (user_info == NULL)
    //         break;
    //     i++;
    //     printf("%d: %s\n", i, user_info->ut_user);
    // }

    return 0;
}

void show_info(struct utmpx* utbufp) {
    // if (utbufp->ut_type != USER_PROCESS) {
    //     printf("show_info... return: type %u, name %s\n", utbufp->ut_type, utbufp->ut_user);
    //     return;
    // }

    printf("%-4.4u", utbufp->ut_type);
    printf(" ");
    printf("%-8.8s", utbufp->ut_user);
    printf(" ");
    printf("%-8.8s", utbufp->ut_host);
    printf(" ");
    printf("%-8.8s", utbufp->ut_line);
    printf(" ");
    printf("%-8.8s", utbufp->ut_id);
    printf(" ");

    showtime(utbufp->ut_tv.tv_sec);

    printf("\n");
}

void showtime(long timeval) {
    char* cp;
    cp = ctime(&timeval);
    printf("%12.12s", cp+4);
}
