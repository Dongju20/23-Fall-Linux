#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define N 5
#define MAXLINE 100

void sinx_taylor(int num_elements, int terms, double* x, double* result)
{
    int pid[N];
    int fd[2*N];

    int* p_fd = fd;
    for(int i=0; i<N; i++) {
        pipe(p_fd);
        p_fd += 2;
    }

    int length;
    char message[MAXLINE];
    char line[MAXLINE];

	for(int i=0; i<num_elements; i++) {

        p_fd = &fd[2*i];
        if((pid[i] = fork()) == 0) { // child
            close(p_fd[0]);

    		double value = x[i];
	    	double numer = x[i] * x[i] * x[i];
		    double denom = 6.; // 3!
    		int sign = -1;

	    	for(int j=1; j<=terms; j++) {
		    	value += (double)sign * numer / denom;
    			numer *= x[i] * x[i];
    			denom *= (2.*(double)j+2.) * (2.*(double)j+3.);
    			sign *= -1;
    		}

	    	result[i] = value;
            sprintf(message, "%lf\n", result[i]);
            length = strlen(message)+1;
            write(p_fd[1], message, length); 
            exit(i);    // send child id as exit status
        } else {    // parent
            close(p_fd[1]);
        }
	}

    int stat;
    for(int i=0; i<N; i++) {
        wait(&stat);
        
        int child_id = stat >> 8;
        read(fd[child_id*2+0], line, MAXLINE);
        result[child_id] = atof(line);
    }
    
}

int main()
{
    double x[N] = {0, M_PI/6.f, M_PI/3.f, M_PI/2.f, 0.134};
    double res[N];
    
    sinx_taylor(N, 3, x, res);

    for(int i=0; i<N; i++) {
        printf("sin(%.2f) by Taylor series = %f\n", x[i], res[i]);
        printf("sin(%.2f) = %f\n", x[i], sin(x[i]));
    }

    return 0;
}

