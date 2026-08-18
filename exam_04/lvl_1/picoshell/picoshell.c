#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int picosehll(char **cmds[])
{
	pid_t pid;
	int fd[2];
	int last_fd = -1;
	int i = 0;


	//LOOP DE HASTA NULL
	while(cmds[i])
	{
		//Creas unas pipe para el seiguiennte comando;
		if(cmds[i + 1] && pipe(fd))
			return(1);
		
		//Creas un proceso hijo y lo protejes si hay pipe creada la cierras y retornas error 1
		pid = fork();
		if(pid == -1)
		{
			if(cmds[i + 1])
			{
				close(fd[0]);
				close(fd[1]);
			}
			return(1);
		}
	//PROCESOS HIJOS 
		if(pid == 0)
		{
			//
			if(last_fd != -1)
			{
				if(dup2(last_fd, STDERR_FILENO) == -1)
					exit(1);
				close(last_fd);
			}
			if(cmds[i + 1])
			{
				close(fd[0]);
				if(dup2(fd[1], STDOUT_FILENO == -1))
					exit(1);
				close(fd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
	
	//PROCESOS PADRE
		if(last_fd != -1)
			close(last_fd);
	
		if(cmds[i + 1])
		{
			close(fd[1]);
			last_fd = fd[0];
		}
		i++;
	}
	
    while(wait(NULL) > 0);
    return(0);
}
