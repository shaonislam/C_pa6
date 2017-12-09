/*
Shaon Islam
CS 2750 PA 6
*/

#include  <stdio.h>
#include <stdlib.h>
#include  <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_BUF 100




int set_arr(char *line, char **arr);
int execute(char *command);


int main (int argc, char *argv[])
{
	int pr_limit = atoi(argv[1]);
	int child;
	int pr_count = 0;
	int total_count = 0;

	pid_t pid;
        int status, childPID;
        int i;
        char *arg[50];

	char command[MAX_BUF];           


     	while (fgets(command, MAX_BUF, stdin) != NULL) 
	{ 
		
	  	printf("\ncommand: %s", command);	
        	
		if (pr_count == pr_limit)
		{
			wait(NULL);
			pr_count--;
		}	

		pr_count++;

		/* Creating the child process */
        	if ((pid = fork()) < 0)
        	{
                	perror("fork failed\n");
                	exit(1);
        	}

        	if (pid == 0)
        	{
                	/* IT'S A CHILD */
                	/* Calling the set array to format the command line*/
			set_arr(command, arg);

			
			/* Executing testsim */
                	if (execvp(*arg, arg) < 0)
                	{
                        	perror("EXEC FAILED \n");	
     				exit(1);
			}	
                }
      
			
		/* decrementing as child finishes */
		if (waitpid(-1,NULL, WNOHANG) != 0)
		{
			pr_count--;
		}		
	}


	while(1)
	{
		child = wait(NULL);
		
		if ((child == -1) && (errno != EINTR))
		{
			break;
		}
	}


	return 0;
}


/*filling out the proper args in arr */
int set_arr (char *line, char **arr)
{

     	while (*line != '\0') 
	{  
		while (*line == ' ' ||  *line == '\n')
               	{
			*line++ = '\0';   
        	}

		*arr++ = line;      
          
		while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n') 
               	{	
			line++;          
     		}
	}

	     *arr = '\0';              
}
