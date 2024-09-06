
#include "philo.h"
#include <unistd.h>

/* ************************************************************************** */
/*  When you create threads using pthread_create, they run concurrently,      */
/*  and you typically need to ensure that they have completed their execution */
/*  before your program  continues or exits. 				      */
/*  pthread_join provides a way to synchronize with these threads.            */

/*	int pthread_create(						      */
/*	pthread_t *thread,						      */
/*	const pthread_attr_t *attr, -> NULL for standsrt		      */
/*	void *(*start_routine)(void *), -> function to do in the new thread   */
/*	void *arg -> arg to make thread working, if no = NULL		      */
/* ************************************************************************** */

int	ft_start_threads(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				&philo_routine, &table->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_join_threads(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
