
//if string contains only digits
//atoi function to convers char to int 
// i can combine this togeter and create a is_valid function

#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int	number_of_philosophers = 10;

bool	contains_digits(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

int	ft_atoi(char *str)
{
	int	i;
	unsigned long long int	res;

	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32 || str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (res > INT_MAX)
		return (-1);
	return ((int)res);
}

bool	is_valid(int ac, char **av)
{
	int	i;
	int	nb;

	i = 1;
	if (ac != 5)
	{
		printf ("argumnets");
		exit(1);
	}
	while (i < ac)
	{
		if (!contains_digits(av[i]))
		{
			printf("mistake 1");
			exit(1);
		}
		nb = ft_atoi(av[i]);
		//check if the first param is valid
		if (i == 1 && (nb <= 0 && nb >= number_of_philosophers))
		{
			printf("mistake 2");
			exit(1);
		}
		if (i != 1 && nb < 0)
		{
			printf ("mistake 3");
			exit(1);
		}
		i++;
	}
	return (true);
}

int main(int ac, char **av)
{
	if (is_valid(ac, av))
		printf("hello everything is fine");
	else 
		printf("MIStAKE");
}
