#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

void show_info(struct utmp *record);
void show_time(int time);
void format_time(const char* date, char formatted[10]);

int main(){
    struct utmp current_record;
    int utmpfd;
    int reclen = sizeof(current_record);
    if( (utmpfd = open(UTMP_FILE, O_RDONLY)) == -1){
        perror(UTMP_FILE);
        exit(EXIT_FAILURE);
    }
    while(read(utmpfd, &current_record, reclen) == reclen){
        if(current_record.ut_type == USER_PROCESS){
            show_info(&current_record);
        }
    }
    close(utmpfd);
    return 0;
}

void show_info(struct utmp *record){
    printf("%-12.12s", record->ut_user);
    printf(" ");
    printf("%-8.8s", record->ut_line);
    printf(" ");
    show_time(record->ut_time);
    if(record->ut_host[0] != '\0')
        printf("(%s)", record->ut_host);
    printf("\n");
}

void show_time(int time){
    char *cp;
    long int conv = time;
    cp = ctime(&conv);
    printf("%20.20s", cp+4);
    printf(" ");
}
