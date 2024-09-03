

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
	{
		printf("arg error\n");
		return (-1);
	}
	if (is_valid(ac, av) == -1)
	{
		printf("mistake\n");
		return (-1);
	}
	if (init_table(ac, av, &table) != 0)
		return (-1);

	/*for checking that it works
	printf("nb_Philo = %zu\n", table.nb_philos);
	printf("time to die = %zu\n", table.time_to_die);
	printf("time to eat = %zu\n", table.time_to_eat);
	printf("time to sleep = %zu\n", table.time_to_sleep);
	printf("must eat count %zu\n", table.must_eat_count);*/

	// Start the philosopher threads
	if (ft_start_threads(&table))
		return (-1);

	return (0);
}
