
//if string contains only digits
//atoi function to convers char to int 
// i can combine this togeter and create a is_valid function

#include "philo.h"

static bool	contains_digits(char *str)
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

static int	ft_atoi(char *str)
{
	int	i;
	int	flag;
	unsigned long long int	res;

	i = 0;
	res = 0;
	flag = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		flag = 1;
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (flag == 0)
		return (EXIT_FAILURE);
	if (res > INT_MAX)
		return (EXIT_FAILURE);
	return ((int)res);
}

bool	is_valid(int ac, char **av)
{
	int	i;
	int	nb;

	i = 1;
	while (i < ac)
	{
		if (!contains_digits(av[i]))
			return (EXIT_FAILURE);
		//check if params are valid
		nb = ft_atoi(av[i]);
		//check if the fisrst param is valid
		if ((i == 1 && nb <= 0) || (i != 1 && nb < 0))
			return (EXIT_FAILURE);
		i++;
	}
	return (true);
}
