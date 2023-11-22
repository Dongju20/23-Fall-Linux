#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int child_id;

void intHandler();
void intHandler2();
void intHandler3();

void printf_gugu(){
	for(int i=0;i<=20;i++){
		for(int j=1;j<=20;j++){
			printf("%d X %d = %d\n",i,j, i*j);
		}
		sleep(1);
		if(i==9)
			signal(SIGINT,intHandler3);
	}
}

int main(){
	int pid;
	if((pid=fork()) == 0){
		signal(SIGINT,intHandler2);
		printf_gugu();
		pause();
	}
	else{
		child_id = pid;
		signal(SIGINT, intHandler);
		wait();
	}
}

void intHandler(){
	kill(child_id,SIGINT);
}

void intHandler2(){
	printf("아직 구구단이 끝나지 않았습니다\n");
}

void intHandler3(){
	kill(-getppid(),SIGKILL);
}
