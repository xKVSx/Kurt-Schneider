/***********************
NAME:  Kurt Schneider  *
COURSE: CECS 326       *
PROGRAM NAME: p2p.c	   *
/***********************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int i,a,b,t,seed,sleeptime;
	pid_t childpid = 0;
	char value[3]; char err_msg[25];

	if(argc !=4) 
	{
		printf("\nUsage: %s processes\n", argv[0]);
		exit(1);
	}

	t = atoi(argv[1]); //sleep time
	a = atoi(argv[2]); //first integer
	b = atoi(argv[3]); //second integer
	
    if(t <0 || t > 50)
	{
		printf("\nValue of t is out of range (0 - 50).\n");
		exit(1);
	}

	printf("\nI am the parent process, the maximum sleep time is %d and the two numbers are %d and %d\n", t, a, b);

	seed = (int)(getpid() + a);
	srand(seed);
	sleeptime = rand() % t;
	sleep(sleeptime);

	for (i=0; i<4; i++)
	{
		if((childpid = fork()) == 0)
		{
			sprintf(value, "%d", i);
			execl("p2c", "p2c", argv[1], argv[2], argv[3], value, (char *) NULL);
			sprintf(err_msg, "%s Exec failure", value);
			perror(err_msg);
			exit(1);
		}
		else if(childpid == -1)
			perror("Fork failure\n");
		else
			printf("Forked child %d\n", childpid);
	}

	exit(0);
}