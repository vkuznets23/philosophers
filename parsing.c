
//if string contains only digits
//atoi function to convers char to int 
// i can combine this togeter and create a is_valid function

#include "philo.h"

int ft_atoi(char *str)
{
    	unsigned long long res = 0;
    	int i = 0;

    	// Skip whitespace
    	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32);
			i++;
	// Convert digits to integer
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		// Check for overflow
        	if (res > INT_MAX)
			return -1; // Indicate overflow error
        	i++;
    	}

    	// If there are trailing characters or no digits at all
    	if (str[i] != '\0')
        	return -1; // Indicate invalid input

    	return (int)res;
}

bool	is_valid(int ac, char **av)
{
	int	i;
	int	nb;

	i = 1;
	while (i < ac)
	{
		//check if params are valid
		nb = ft_atoi(av[i]);
		if (nb < 0)
			return (false);
		//check if the fisrst param is valid
		if (i == 1 && nb <= 0)
			return (false);
		i++;
	}
	return (true);
}
