

#include "philo.h"

int init_forks(t_table *table)
{
    unsigned int i;

    table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
    if (!table->forks)
        return -1; // Indicate failure

    i = 0;
    while (i < table->nb_philos) 
    {
        if (pthread_mutex_init(&table->forks[i], NULL) != 0) 
	{
            // Cleanup on failure (let's say it accures after a couple succesful ones
            while (i > 0)
                pthread_mutex_destroy(&table->forks[--i]);
            free(table->forks);
            return -1; // Indicate failure
        }
	i++;
    }
    return 0; // Success
}

int	init_philosophers(t_table *table)
{
	unsigned int	i;

	table->philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (!table->philos)
		return -1;
	i = 0;
	while (i < table->nb_philos)
	{
		//Each philosopher has a number ranging from 1 to number_of_philosophers.
		table->philos[i].id = i + 1; 
		table->philos[i].table = table;
		table->philos[i].no_ate = 0;
		table->philos[i].fork_l = &table->forks[i];
		table->philos[i].fork_r = &table->forks[(i + 1) % table->nb_philos];
		table->philos[i].lst_eating = table->start;

		//printing to check
		/*printf("Philosopher %zu initialized:\n", table->philos[i].id);
        	printf("  Fork Left: %ld\n", table->philos[i].fork_l - table->forks);
       	 	printf("  Fork Right: %ld\n", table->philos[i].fork_r - table->forks);*/
		i++;
	}
	return 0;
}

int	init_table_mutexes(t_table *table)
{
	// Initialize the mutexes for the table's state and printing
	if (pthread_mutex_init(&table->locks, NULL) != 0)
		return -1; // Indicate failure
	if (pthread_mutex_init(&table->print_locks, NULL) != 0)
	{
		pthread_mutex_destroy(&table->locks); // Clean up previous mutex
		return -1; // Indicate failure
	}
	return 0; // Success
}

/* init_table:
*	Initializes the "dining table", the data structure containing
*	all of the program's parameters.
*	Returns a pointer to the allocated table structure, or NULL if
*	an error occured during initialization.
*/
int	init_table(int ac, char **av, t_table *table)
{
	table->nb_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->must_eat_count = 0;
	table->dead_or_full = 0;
	table->start = get_time();
	if (ac == 6)
		table->must_eat_count = ft_atoi(av[5]);
	if (init_philosophers(table) != 0)
    	{
        	free(table);
        	return -1; // Handle philosopher initialization failure
    	}
	// Initialize forks or other necessary components here
    	if (init_forks(table) != 0)
   	 {
        	free(table->philos);
        	free(table);
        	return -1; // Handle fork initialization failure
   	 }

	//also need to initialize mutexes for locks and print_locks!!!!
	if (init_table_mutexes(table) != 0)
	{
		free(table->philos);
		free(table->forks);
		return -1; // Handle mutex initialization failure
	}
	return (0);
}
