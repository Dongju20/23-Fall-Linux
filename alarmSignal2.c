#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void intHandler();
void intHandler2();


int main(){
	signal(SIGALRM,intHandler);
	signal(SIGINT,intHandler2);
	alram(10);
	int correct = 0;
	while(!correct){
		if(getchar() == '1'){
			if(getchar() =='2'){
				if(getchar()=='\n'){
					correct =1;
				}
			}
		}

	}
	printf("End of main \n");
}

void intHandler(){
	printf("Fire!\n");
	eixt(0);
}

void intHandler2(){
	printf("10sec reset...\n");
	alarm(10);
}
