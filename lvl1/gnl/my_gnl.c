#include <fcntl.h> // testing
#include <stdio.h> // testing
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

int ft_strlen(char *str)
{
	int i= 0;
	if (!str)
		return(0);
	while(str[i])
		i++;
	return(i);
}
char	*ft_strdup(char *str)
{
	char	*dest;
	int		i;
	int len;

	i = 0;
	len = ft_strlen(str);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	while (str[i++])
		dest[i] = str[i];
	dest[i] = '\0';
	return (dest);
}
char	*get_next_line(int fd)
{
	static int index;//este indice del buff
	static int bits;
	static char buff[BUFFER_SIZE];
	int i = 0;// indice para linea
	char line[70000];
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (index >= bits) // cada vez que el bucle comprueba que el index sea menor a bits 
		{
			//la primera lectura se realiza y luego comprueba
			bits = read(fd, buff, BUFFER_SIZE);
			index = 0;// reseteo de index para poder comparar con la cantidad de bits leidos
			if (bits <= 0)// error de lectua
				break ;
		}
		line[i++] = buff[index++];
		if (line[i - 1] == '\n')// compueba que tiene toda la linea;
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}
