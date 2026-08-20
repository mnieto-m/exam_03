#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int picoshell(char **cmds[])
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
		
	//HIJO		
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
		/* CONFIGURO FDS */
		if(pid == 0)
		{
			/* RECIBO COMANDO ANTERIOR. */
			if(last_fd != -1)
			{
				if(dup2(last_fd, STDIN_FILENO) == -1)
					exit(1);
				close(last_fd);
			}
			/* PREPARO SIGUIENTE COMANDO */
			if(cmds[i + 1])
			{
			// CIERRO FD DE ENTRADA; CLONO DE SALIDA Y CIERRO EL ORIGINAL;
				close(fd[0]);
				if(dup2(fd[1], STDOUT_FILENO == -1))
					exit(1);
				close(fd[1]);
			}
			//EJECUTO
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
	//PADRE
		// CIERRO LOS FDS ABIERTOS PARA LECTURA
		if(last_fd != -1)
				close(last_fd);
	
		/* Si existe un siguiente comando, conserva el extremo de lectura
		 * para usarlo como entrada en la siguiente iteracion. */
		if(cmds[i + 1])
		{
			close(fd[1]);
			last_fd = fd[0];
		}
		//ITERO
		i++;
	}
	
    while(wait(NULL) > 0);
    return(0);
}
