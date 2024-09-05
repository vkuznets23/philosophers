
//if string contains only digits
//atoi function to convers char to int 
// i can combine this togeter and create a is_valid function

#include "philo.h"

// Corrected ft_atoi function
int ft_atoi(char *str)
{
    unsigned long long res = 0;
    int i = 0;

    // Skip whitespace
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        i++;

    // Handle optional '+' sign
    if (str[i] == '+')
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

    // Ensure the result fits in an int
    if (res > INT_MAX)
        return -1; // Indicate overflow error

    return (int)res;
}

/*size_t	ft_ptoi(char *str, size_t *num)
{
	size_t	res;

	res = 0;
	while ('0' <= *str && *str <= '9')
		res = res * 10 + *str++ - 48;
	if (*str || res == 0)
		return (ft_usage(), 1);
	*num = res;
	return (num);
}*/

int	is_valid(int ac, char **av)
{
	int	i;
	int	nb;

	i = 1;
	while (i < ac)
	{
		nb = ft_atoi(av[i]);
		if (nb <= 0)
			return (-1);
		i++;
	}
	return (0);
}
