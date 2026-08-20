#include "vbc.h"

char *s;

void error(char c)
{
	if(c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of file\n");
}

int ft_sum()
{
	int a;

	a = ft_mult();
	while (*s == '+')
	{
		s++;
		a += ft_mult();
	}
	return (a);
}
int ft_product()
{
	int c;

	c = ft_factor();
	while (*s == '*')
	{
		s++;
		c *= ft_factor();
	}
	return (c);

}
int ft_factor()
{
	int n = 0;

	if (isdigit(*s))
		return (*s++ - '0');
	if (*s == '(')
	{
		s++;
		n = ft_sum();
		s++;
	}
	return (n);
}
int checker(char *str)
{
	int i = 0;
	int par = 0;
	char last = '\0';

	while(str[i])
	{
		if(str[i] == '(')
			par ++;
		else if(str[i] == ')')
			par --;
		else if (!isdigit(str[i]) && str[i] != '+' && str[i] != '*' && str[i] != '(' && str[i] != ')')
			return(error(str[i]), 1);
		if(isdigit(str[i]) && isdigit(str[i + 1]))
			return(error(str[i + 1]), 1);
		last = str[i];
		i++;
	}
	if(par > 0)
		return(error('('),1);
	if(par < 0)
		return(error(')'),1);
	if(last == '+'|| last == '*')
		return(error(0),1);
	return(0);
}
int main(int argc, char **argv)
{
	int result;

	if(argc != 2)
		return(1);
	if(checker(argv[1]))
		return(1);
	s = argv[1];

	result = ft_sum();
	printf("%d\n", result);
}