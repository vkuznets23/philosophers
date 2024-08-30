

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	if (ac - 1 < 4 || ac - 1 > 5)
	{
		printf("arg error§");
		exit (1);
	}
	if (!(is_valid(ac, av)))
	{
		printf("mistake");
		return (EXIT_FAILURE);
	}

}
