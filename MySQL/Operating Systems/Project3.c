/***********************************************************************************
DESCRIPTION: The program generates three processes.  The input to the parent       *
			 program includes a text.dat file (created by the user), an integer for*
			 the number of tries a child process will attempt to obtain the lock   *
			 file and an integer for the maximum amount of time a child process    *
			 can sleep if it fails to obtain the lock file.  The parent program    *
			 will call a seperate child program for each child process and wait for*
			 the return status of each child process.                              *
/***********************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	int k, status, num_tries, t;
	pid_t pid = 0, w;
	char c_num[3]; char err_msg[25];

	/*argv[0] = parent process code
	argv[1] = text.dat
	argv[2] = number of tries
	argv[3] = sleeptime value*/

	if(argc != 4)
	{
		printf("\nUsage %s processes\n", argv[0]);
		exit(1);
	}

	num_tries = atoi(argv[2]); //number of tries
	t = atoi(argv[3]); //sleep time value

	if(num_tries < 0)
	{
		printf("Number of tries must be positive\n");
		exit(1);
	}
	
	if(t <= 0)
	{
		printf("sleep time must be greater than zero\n");
		exit(1);
	}
	
	//remove any leftover lock files
	if(unlink("lock") == 0)
		printf("\nFile lock is released\n");
	else
		printf("\nFile lock does not exist\n");

	/*The loop creates three child processes.  The execl function is used to call
	  a seperate child program for each child process.*/
	for(k = 0; k<3; k++)
	{
		if((pid = fork()) == 0)	//child process
		{
			sprintf(c_num, "%d", k); //k is the child number based on the order of creation
			execl("p3c", "p3c", argv[1], argv[2], argv[3], c_num, (char *) NULL);
			sprintf(err_msg, "%s Exec failure", c_num);
			perror(err_msg);
			exit(1);
		}
		else if(pid == -1)
			perror("Fork failure\n");
	}
	
	/*waiting for child program.  w is the pid number of the
	returning child process.*/
	while((w = wait(&status)) && w != -1)
	{
		if(w != -1)
			printf("\nWait on PID: %d returns status of: %04X\n", w, status);	
	}
	exit(0);
}



	
