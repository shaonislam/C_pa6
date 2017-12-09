#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUF 100


/* execvp(command, argument) */


int main (int argc, char *argv[]) 
{
	int pr_limit, status;
	int pr_count = 0;
	pid_t childpid;
	int i;
	char cmd[MAX_BUF]; 

	if (argc != 2)
	{ 
 		fprintf(stderr, "Usage: %s processes\n", argv[0]);
 		return 1;
 	}
 
	/* Setting of number of processes to run at a time */
	pr_limit = atoi(argv[1]);


	/*Main loop through whole testing.data */
	while (fgets(cmd, MAX_BUF - 1, stdin) != NULL)
	{
		if (pr_limit == pr_count)
		{
			wait(NULL);
			pr_count--;
		}

		/* Execute the program: fork a child and execute file */
		
		childpid = fork();
		
		/* Check if child is created properly */
		if (childpid < 0)
		{
			printf("\nFailed to create child.\n");
			return 1;
		}

		/* Increment Number of Active Children */
		pr_count++;


		/* Check to see if any children have finished */
		waitpid(-1, &status, WNOHANG);
		

	}




/*
	for (i = 1; i < pr_limit; i++)
 		if ((childpid = fork()) <= 0)
 			break;
 
	fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n" ,i, getpid(), getppid(), childpid);
*/





 
	return 0;
}
