/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_filter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:11:40 by mnieto-m          #+#    #+#             */
/*   Updated: 2025/10/23 20:44:03 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

ft_filter(char* buffer, char*  index)
{
	int i = 0;//iterador de buffer
	int j = 0;// iterador de index
	int len = ft_strlen(index);
	
	while(buffer[i])
	{
		j = 0;
		while(buffer[i + j] == index[j])// iterar para encontrar primera concurrencia
			j++;
		if(j == len)
		{
			while(--j > 0)
				write(1,"*",1);
			i += len;
		}
		else//imprime si no encutra la concurrencia
		{
			write(1,&buffer[i],1);
			i++;
		}
	}
}

ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s && s[i] != 0)
		i++;
	return(i);
}

int main(int argc, char **argv)
{
	int i = 0;
	int r = 0;
	char buffer[999];
	if( argc != 2 || argv[1] == NULL ||  ft_strlen(argv[1]) == 0 )
		return(1);
	while(r > 0)
	{
		r = read(0, &buffer[i],0);
		i += r;	
	}
	buffer[i] = '\0';
	filter(buffer, argv[1]);
}