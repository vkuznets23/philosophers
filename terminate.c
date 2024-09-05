
#include "philo.h"

/* ************************************************************************** */
/* This function terminate whole process:                                     */
/* 	destroy all fork mutexes and general mutex					      */
/*	free space that was malloced for forks and philos		      */
/* ************************************************************************** */

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
	pthread_mutex_destroy(&table->locks);
}
