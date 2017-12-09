#include  <stdio.h>
#include <stdlib.h>
#include  <sys/types.h>
#include <sys/wait.h>


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
	int i = 0;;

	char command[MAX_BUF];           
/*	char *cmd_array[50];	*/

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

		execute(command);

	 /* 	set_arr(command, cmd_array);  
		execute(cmd_array);	*/			
     	

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


	return 0;
}



/*int execute(char **argv)*/
int execute(char *command)
{

	pid_t pid;
	int status, childPID;
	int i;


	char *argv[50];

	
	if ((pid = fork()) < 0)
	{
		printf("FORK FAILED\n");
		exit(1);
	}
	
	if (pid == 0) 
	{
		/* IT'S A CHILD */
		printf("CHILD %ld created!\n", getpid());
		
		/*latest line*/
		set_arr(command, argv);
		
		


		if (execvp(*argv, argv) < 0)
		{
			printf("EXEC FAILED NOOO\n");
			exit(1);
		}
	}
	
	if (pid > 0)
	{
		/* IT'S THE MOM */
		childPID = wait(&status);
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
