/*Takes one command-line arg that specifies the max number of simultaneous
executions */

/* runs programs up to  pr_limit */
/* specifies number of children allowed to execute at a time */
/* pr_count holds the number of active children - init = 0;
/* decrement pr_count everytime child completes */
/* MAX_BUF */
/* Exit after all the children are finished */
/* testsim.c takes sleep time and repeat factor */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUF 100

int main (int argc, char *argv[]) 
{
	int pr_limit;
	int pr_count = 0;
	


	pid_t childpid = 0;

 	int i;
 
	if (argc != 2)
	{ 
 		fprintf(stderr, "Usage: %s processes\n", argv[0]);
 		return 1;
 	}
 
	pr_limit = atoi(argv[1]);

	for (i = 1; i < pr_limit; i++)
 		if ((childpid = fork()) <= 0)
 			break;
 
	fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n" ,i, getpid(), getppid(), childpid);
 
	return 0;
}
