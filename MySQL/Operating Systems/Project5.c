/***********************************************************************************
DESCRIPTION:  The purpose of the program is to create a chain of processes, where  *
each process writes its child number, process identification number, its parent’s  *
process identification number and its child process identification number into a   *
shared buffer, which will act as a critical section for each process.  The shared  *
buffer will then be displayed with two different options.  The first option is to  *
allow semaphore protection of the critical section and the second option is to use *
the shared buffer and display without protection.  If the process does not have a  *
child, the child process identification number is 0.  Each process will have       *
exactly one child process, except for the last process in the chain, which will    *
have no children.  The child number corresponds to the generation of each process. * 
For example, the first child created is second generation and will have child      *
number 1 (generations start at 0).  The program accepts three arguments, which are *
the number of processes to be created, an “s” or “n” character representing        *
protection and no protection respectively and a delay adjustment parameter.  The   *
purpose of the delay adjustment parameter is to slow the speed of the display      *
process to show that without semaphore protection the displayed contents of the    *
buffer are randomly interleaved.  However, in this program the mechanism of the    *
slowing this process does not utilize the delay adjustment parameter.  Instead,    *
the delay is accomplished by writing each message to a separate buffer and then    *
displaying each character individually.  After the character is displayed, the     *
process will sleep.  This will show that without semaphore protection, the message *
will be randomly interleaved.                                                       
			                                                                       *
INVOCATION: N = number of processes                                                *
			i, j = counter														   *
			cbuffer[], temp[] = temporary buffers used to display process info     *
			set_sembuf_struct() = intiliaize for p or v operation                  *
			p() = P operation                                                      *
			v() = V operation                                                      *
/***********************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
char *cbuffer[50]; //temporary buffer  
char *temp[1];

union semun
{
	int val;
	struct semid_ds *buf;
	ushort *array;
};

void set_sembuf_struct(struct sembuf *s, int semnum, int semop, int semflg);
void p(int *semid, int *semop_ret, struct sembuf *semwait);
void v(int *semid, int *semop_ret, struct sembuf *semsignal);

int main(int argc, char *argv[])
{
	int N, sem_value, semid, semop_ret, status, i, j;
	key_t ipc_key;
	pid_t childpid, w;
	static ushort sem_array[1] = {1};
	struct semid_ds sem_buf;
	union semun arg;
	ipc_key = ftok(".", 'S');
	struct sembuf semwait[1];   
	struct sembuf semsignal[1];

	/*semid is a unique semaphore identifier.
	ipc_key is the key used to generate a unique semaphore identifier.
	sum_buf is the name given to the semaphore data structure.
	arg is a union of type semun.*/

	if(argc <= 3)
	{
		printf("\nNot enough arguments\n");
		exit(1);
	}

	//number of processes to create
	N = atoi(argv[1]); 

	if(N <= 0)
	{
		printf("\nNumber of child processes must be greater than zero\n");
		exit(1);
	}
	else if(N > 100)
	{
		printf("\nNumber of child processes must be less than 100\n");
		exit(1);
	}
	else if(*argv[2] != 115 && *argv[2] != 110)  //115 is the ascii value for s and n is 110
	{
		printf("\nInvalid argument: %s", argv[2]);
		exit(1);
	}
	
	//check for existing semaphore	
	semid = semget(ipc_key, 0, 0 | 0666);

	if(semid >= 0)
	{	//remove existing semaphore
		if(semctl(semid, 0, IPC_RMID, 0) == -1)				        
		{
 			perror("semctl: IPC_RMID");
			exit(5);
		}				
	}

	//create new semaphore
	if((semid = semget(ipc_key, 1, IPC_CREAT | IPC_EXCL | 0666)) == -1)
	{
		perror("semget: IPC | 0666");
		exit(1);
	}

	/*set arg(the union) to the address of the storage location for
	returned semid_ds value*/
	arg.buf = &sem_buf;

	if(semctl(semid, 0, IPC_STAT, arg) == -1)
	{
		perror("semctl: IPC_STAT");
		exit(2);
	}

	//set arg(the union) to the address of the initializing vector
	arg.array = sem_array;

	/*initializes the semaphore in the set to the value stored in sem_array
	which is referenced by arg.*/
	if(semctl(semid, 0, SETALL, arg) == -1)
	{
		perror("semctl: SETALL");
		exit(3);
	}

	//generate a chain of children of N length
	for(i = 0; i < N; i++)
	{
		if((childpid = fork()) == -1)
			perror("Fork failure\n");
		else if(childpid > 0)
			break;
	}	

	//semaphore protection
	if(*argv[2] == 115)
	{
		set_sembuf_struct(semwait, 0, -1, 0);
		p(&semid, &semop_ret, &semwait);
	
	}
	
	/***********************************************************************************
	CRITICAL SECTION*/
	sprintf(cbuffer, "%d process ID: %d parent ID: %d child ID: %d\n", i, getpid(), getppid(), childpid);

	//delay the display of each process
	for(j= 0; j < 50; j++)
	{
		*temp = cbuffer[j];
		printf(temp);
		fflush(stdout);
		sleep(1);
	}
	/*CRITICAL SECTION
	*************************************************************************************/

	//semaphore protection
	if(*argv[2] == 115)
	{
		set_sembuf_struct(semsignal, 0, 1, 0);
		v(&semid, &semop_ret, &semsignal);
		
	}

	while((w = wait(&status)) && w != -1)

	exit(0);

}

void set_sembuf_struct(struct sembuf *s, int semnum, int semop, int semflg)
{
	s->sem_num = (short)semnum;
	s->sem_op =semop;
	s->sem_flg = semflg;
	return;
}

void p(int *semid, int *semop_ret, struct sembuf *semwait)
{
	while(((*semop_ret = semop(*semid, semwait, 1)) == -1) && (errno == EINTR));
	{
		if(*semop_ret == -1)
			printf("%ld: semaphore decrement failed - %s\n", (long)getpid(), strerror(errno));
	}
}

void v(int *semid, int *semop_ret, struct sembuf *semsignal)
{
	while(((*semop_ret = semop(*semid, semsignal, 1)) == -1) && (errno == EINTR));
	{
		if(*semop_ret == -1)
			printf("%ld: semaphore increment failed - %s\n", (long)getpid(), strerror(errno));
	}
}