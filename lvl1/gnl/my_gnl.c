#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h> // testing
#include <stdio.h> // testing

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 32
#endif

char	*ft_strdup(char *str)
{
	char	*dest;
	int i = 0;
	while (str[i])
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	i = -1;
	while (str[++i])
		dest[i] = str[i];
	dest[i] = '\0';
	return (dest);
}
char	*get_next_line(int fd)
{
	static char buff[BUFFER_SIZE];
	static int bpos;
	static int bread;
	char line[70000];
	int i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (bpos >= bread)
		{
			bread = read(fd, buff, BUFFER_SIZE);
			bpos = 0;
			if (bread <= 0)
				break;
		}
		line[i++] = buff[bpos++];
		if (line[i -1] == '\n')
			break;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}