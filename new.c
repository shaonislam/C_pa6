#include  <stdio.h>
#include <stdlib.h>
#include  <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_BUF 1024




int set_arr(char *line, char **arr);
/*int execute(char **argv);*/
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
		total_count++;


        	if ((pid = fork()) < 0)
        	{
                	printf("FORK FAILED\n");
                	exit(1);
        	}

        	if (pid == 0)
        	{
                	/* IT'S A CHILD */
                	printf("CHILD %ld created!\n", getpid());
			set_arr(command, arg);

                	if (execvp(*arg, arg) < 0)
                	{
                        	printf("EXEC FAILED NOOO\n");	
     				exit(1);
			}	
                }
      


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



int set_arr (char *line, char **arr)
{

     	while (*line != '\0') 
	{  
		while (*line == ' ' || *line == '\t' || *line == '\n')
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
