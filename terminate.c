
#include "philo.h"

void	ft_terminate(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->philos);
	free(table->forks);
	// Destroy the general locks
    	pthread_mutex_destroy(&table->locks);
}

