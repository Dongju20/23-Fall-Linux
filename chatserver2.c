#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <errno.h>
#define MAXLINE 256

int fd1, fd2, fd3, fd4;

void setNonBlocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void *ReadC1AndSendC2(){
         int n;
         char msg[MAXLINE];
         while (1) {
        // fd2로부터 읽기 (non-blocking)
        n = read(fd2, msg, MAXLINE);
        if(n==-1){
                break;
        }
        else{
		  // 데이터를 읽었다면 fd3으로 쓰기 (non-blocking)
            write(fd3, msg, strlen(msg) + 1);

        }
}
}


void *ReadC2AndSendC1(){
         ssize_t bytes_read;
         char msg[MAXLINE];
         int n;
         while (1) {
        // fd4로부터 읽기 (non-blocking)
        n = read(fd4, msg, MAXLINE);
        if(n == -1){
                //데이터가 도착하지 않으면
                break;
        }
        else{
            // 데이터를 읽었다면 fd1으로 쓰기 (non-blocking)
            write(fd1, msg, strlen(msg) + 1);
                }
	 }
}
int main() {
    int n;
    char msg[MAXLINE];
    pthread_t t1, t2;
    if (mkfifo("./chatfifo1", 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    if (mkfifo("./chatfifo2", 0666) == -1) {
        perror("mkfifo");
        exit(2);
    }
   if (mkfifo("./chatfifo3", 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    if (mkfifo("./chatfifo4", 0666) == -1) {
        perror("mkfifo");
        exit(2);
    }

    fd1 = open("./chatfifo1", O_WRONLY);
    fd2 = open("./chatfifo2", O_RDONLY);
    fd3 = open("./chatfifo3", O_WRONLY);
    fd4 = open("./chatfifo4", O_RDONLY);

    if (fd1 == -1 || fd2 == -1 || fd3 == -1 || fd4 == -1) {
        perror("open");
        exit(3);
    }

    printf("서버 시작\n");
    pthread_create(&t1, NULL, ReadC1AndSendC2, NULL);
    pthread_create(&t2, NULL, ReadC2AndSendC1, NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    return 0;
}

