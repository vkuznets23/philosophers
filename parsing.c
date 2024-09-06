
#include "philo.h"

/* ************************************************************************** */
/* skip whitespaces -> iterate through each char of the string                */
/* -> convert char to corresponding number -> check for overflow              */
/* check if there are any non digit characters after parsing                  */
/* Assign the result to the provided pointer                                  */
/* ************************************************************************** */

int	ft_ctos(const char *str, size_t *result)
{
	size_t	res;
	size_t	digit;

	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (res > (SIZE_MAX - digit) / 10)
			return (1);
		res = res * 10 + digit;
		str++;
	}
	if (*str != '\0')
		return (1);
	*result = res;
	return (0);
}

int	is_valid(int ac, char **av)
{
	int		i;
	size_t	nb;

	i = 1;
	while (i < ac)
	{
		if (ft_ctos(av[i], &nb) != 0)
			return (1);
		if (nb <= 0)
			return (1);
		i++;
	}
	return (0);
}
