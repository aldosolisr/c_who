#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <unistd.h>
#include <fcntl.h>

void show_info(struct utmp *record);

int main(){
    struct utmp current_record;
    int utmpfd;
    int reclen = sizeof(current_record);
    if( (utmpfd = open(UTMP_FILE, O_RDONLY)) == -1){
        perror(UTMP_FILE);
        exit(EXIT_FAILURE);
    }
    while(read(utmpfd, &current_record, reclen) == reclen){
        show_info(&current_record);
    }
    close(utmpfd);
    return 0;
}

void show_info(struct utmp *record){
    printf("%-15.15s", record->ut_name);
    printf(" ");
    printf("%-8.8s", record->ut_line);
    printf(" ");
    printf("%10d", record->ut_time);
    printf(" ");
    printf("(%s)", record->ut_host);
    printf("\n");
}
