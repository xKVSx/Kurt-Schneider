/***********************************************************************************
DESCRIPTION:  The program creates NS semaphores in a semaphore set, where NS is an *
			  integer value passed via the command line.  The program also has the *
			  option to remove any existing semaphore sets prior to creating a new *
			  set, or not removing any existing semaphore sets.  If this option is *
			  chosen and a set already exist, the program will display an error    *
			  message that the semaphore set already exist.                        *
/***********************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<unistd.h>
#include<stdlib.h>

union semun
{
	int val;
	struct semid_ds *buf;
	ushort *array;
};

int main(int argc, char *argv[])
{
	int NS, sem_id, sem_value, i, v; 
	key_t ipc_key;
	static ushort sem_array[100]; //100 is the maximum number of values
	struct semid_ds sem_buf;
	union semun arg;
	ipc_key = ftok(".", 'S');

	/*NS is the number of semaphores in the set.
	sem_id is a unique semaphore identifier.
	sem_value is the value given to each semaphore in the set.
	i is used as a counter to place each semaphore value into sem_array
	v is used as a temp variable to hold the semaphore value.
	ipc_key is the key used to generate a unique semaphore identifier.
	sum_buf is the name given to the semaphore data structure.
	arg is a union of type semun.*/

	if(argc <= 2)
	{
		printf("\nNot enough arguments\n");
		exit(1);
	}

	NS = atoi(argv[2]); // number of semaphores

	if(argc - 3 != NS) 
	{
		printf("\nArguments do not match\n");
		exit(1);
	}
	else if(NS <= 0)
	{
		printf("\nNumber of semphores must be greater than zero\n");
		exit(1);
	}
	else if(NS > 100)
	{
		printf("\nNumber of semphores must be less than 100\n");
		exit(1);
	}
	else if(*argv[1] != 114 && *argv[1] != 110)  //114 is the ascii value for r and n is 110
	{
		printf("\nInvalid argument: %s", argv[1]);
		exit(1);
	}

	for(i = 0; i < NS; i++)
	{
		v = atoi(argv[i + 3]);
		sem_array[i] = v; //place semaphore values into array
	}

	//check for existing semaphore
	sem_id = semget(ipc_key, 0, 0 | 0666);

	if(sem_id >= 0 && *argv[1] == 114)
	{	//semaphore exist and 'r' is true
		//remove existing semaphore
 		if(semctl(sem_id, 0, IPC_RMID, 0) == -1)				        
		{
 			perror("semctl: IPC_RMID");
			exit(5);
		}				
	}
	
	//create new semaphore.  If semaphore already exist, print error message.
	if((sem_id = semget(ipc_key, NS, IPC_CREAT | IPC_EXCL | 0666)) == -1)
	{
		perror("semget: IPC | 0666");
		exit(1);
	}

	printf("Semaphore identifier %d\n", sem_id);

	/*set arg(the union) to the address of the storage location for
	returned semid_ds value*/
	arg.buf = &sem_buf;

	/*returns the current values of sum_buf for the indicated
	semaphore indentifer.  The returned information is stored in arg.*/
	if(semctl(sem_id, 0, IPC_STAT, arg) == -1)
	{
		perror("semctl: IPC_STAT");
		exit(2);
	}
	
	//print time and date semaphore was created
	printf("Create %s", ctime(&sem_buf.sem_ctime));

	//set arg(the union) to the address of the initializing vector
	arg.array = sem_array;

	/*initializes all semaphores in the set to the values stored in sem_array
	which is referenced by arg.*/
	if(semctl(sem_id, 0, SETALL, arg) == -1)
	{
		perror("semctl: SETALL");
		exit(3);
	}

	/*return the current value of the individual semaphores referenced
	by the value of i*/
	for(i = 0; i < NS; ++i)
	{
		if((sem_value = semctl(sem_id, i, GETVAL, 0)) == -1)
		{
			perror("semctl: GETVAL");
			exit(4);
		}	
		printf("Semaphore %d has value of %d\n", i, sem_value);
	}

	exit(0);
}