

#include "philo.h"

int init_forks(t_table *table)
{
    unsigned int i;

    table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
    if (!table->forks) {
        return -1; // Indicate failure
    }

    i = 0;
    while (i < table->nb_philos) 
    {
        if (pthread_mutex_init(&table->forks[i++], NULL) != 0) 
	{
            // Cleanup on failure (let's say it accures after a couple succesful ones
            while (i > 0)
                pthread_mutex_destroy(&table->forks[--i]);
            free(table->forks);
            return -1; // Indicate failure
        }
    }
    return 0; // Success
}

/* assign_forks:
*	Assigns two fork IDs to each philosopher. Philosophers with even IDs
*	will have their fork order reversed. This adjustment is necessary because
*	the order in which philosophers pick up their forks can lead to deadlock.
*
*	For example, with 3 philosophers:
*		Philosopher #1 (ID: 0) will attempt to take fork 0 and fork 1.
*		Philosopher #2 (ID: 1) will attempt to take fork 1 and fork 2.
*		Philosopher #3 (ID: 2) will attempt to take fork 2 and fork 0.
*	If philosopher #1 takes fork 0, philosopher #2 takes fork 1, and philosopher #3 takes fork 2,
*	a deadlock occurs because each philosopher will be waiting for their second fork, which is
*	already held by another philosopher.
*
*	Reversing the fork order for even-numbered philosophers helps to avoid deadlock:
*		Philosopher #1 (ID: 0) will take fork 1 first, then fork 0.
*		Philosopher #2 (ID: 1) will take fork 1 first, then fork 2.
*		Philosopher #3 (ID: 2) will take fork 0 first, then fork 2.
*	Now, philosopher #1 takes fork 1, philosopher #3 takes fork 0, and philosopher #2 waits patiently.
*	Fork 2 is free for philosopher #3 to take, so he can eat. When he finishes, philosopher #1 can
*	take fork 0 and eat. Once he is done, philosopher #2 can finally pick up fork 1 and eat.
*/
void	assign_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->table->nb_philos;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->table->nb_philos;
		philo->fork[1] = philo->id;
	}
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
		table->philos[i] = malloc(sizeof(t_philo));
		if (!table->philos[i])
        	{
            		// Free previously allocated philosophers and return failure
            		while (i > 0)
                		free(table->philos[--i]);
	    		free(table->philos);
	    		return -1;
        	}
		table->philos[i]->id = i;
		table->philos[i]->table = table;
		assign_forks(table->philos[i]);
		i++;
	}
	return 0;
}

/* init_table:
*	Initializes the "dining table", the data structure containing
*	all of the program's parameters.
*	Returns a pointer to the allocated table structure, or NULL if
*	an error occured during initialization.
*/
t_table	*init_table(int ac, char **av, t_table *table)
{
	table->nb_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->must_eat_count = ft_atoi(av[5]);
	if (init_philosophers(table) != 0)
    	{
        	free(table);
        	return NULL; // Handle philosopher initialization failure
    	}
	// Initialize forks or other necessary components here
    	if (init_forks(table) != 0)
   	 {
        	free(table->philos);
        	free(table);
        	return NULL; // Handle fork initialization failure
   	 }
	//smth else
	return (table);
}

int	main(int ac, char **av)
{
	t_table	table;

	table = NULL;
	if (ac < 5 || ac > 6)
	{
		printf("arg error");
		exit (1);
	}
	if (!(is_valid(ac, av)))
	{
		printf("mistake");
		return (EXIT_FAILURE);
	}
	table = init_table(ac, av);
	if (!table)
		return (EXIT_FAILURE);

}
