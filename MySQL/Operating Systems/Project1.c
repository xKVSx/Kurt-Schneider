/***********************************************************************************
DESCRIPTION: The program generates a binary tree of processes.  The input includes *
             the number of levels in the tree.  The maxinum number of levels is 5. *
			 For each process, the program will list the level of the process,     *
			 the process ID, parent ID and the ID of both children. Prior to the   *
			 print statement, there is also a random sleep time for each process.  *
/***********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int i, lvls, seed, sleeptime, m = 4;
	pid_t childpid1 = 0, childpid2 = 0;

	lvls = atoi(argv[1]); //# of levels in the tree
	
	if (argc !=2) 
	{
		printf("\nUsage: %s processes\n", argv[0]);
		exit(1);
	}
	else if (lvls > 5 || lvls <= 0)
	{
		printf("\nThe maximum number of levels is 5.\n");
		exit(1);
	}

	printf("Lvl Procs Parent Child1 Child2\n");
	printf("     ID     ID     ID     ID\n\n");

	for (i=0; i<lvls; i++)
	{
		if (childpid1 = fork())
		{
			if (childpid1 == -1)
			{
				perror ("\nThe fork failed\n");
				exit(1);
			}
			else if(childpid1 != 0)
			{
				childpid2 = fork();
				if (childpid2 == -1)
				{
					perror ("\nThe fork failed\n");
					exit(1);
				}
				else if(childpid2 != 0)
					break;
			}
			childpid1 = 0;	//reinitialize
		}
	}
    seed = (int)(getpid() + childpid1);
	srand(seed);
	/*since each process has a different childpid, using the childpid as the seed number 
	restarts the random function, resulting in a different sleeptime for each process*/
	sleeptime = rand()%m;
	sleep(sleeptime);

	printf(" %d %6ld %6ld %6ld %6ld\n",i, (long)getpid(), (long)getppid(), (long)childpid1, (long)childpid2);

	exit(0);
}
