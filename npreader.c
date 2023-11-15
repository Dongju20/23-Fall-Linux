#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAXLINE 101
/* 이름있는파이프를통해읽은내용을프린트한다. */
int main( ) 
{
	int fd;
	char str[MAXLINE];
	unlink("myPipe");
	mkfifo("myPipe", 0660);
	fd= open("myPipe", O_RDONLY);
	while (readLine(fd, str))
		printf("%s \n", str);
	close(fd);
	return 0;
} 
intreadLine(intfd, char *str)
{ 
	int n;
	do 
	{
		n = read(fd, str, 1);
	} 
	while (n > 0 && *str++ != NULL);
	return (n > 0);

