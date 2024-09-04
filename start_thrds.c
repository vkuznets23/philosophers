
#include "philo.h"
#include <unistd.h>

/******************************************************************************************
*  When you create threads using pthread_create, they run concurrently, and you           *
*  typically need to ensure that they have completed their execution before your program  *
*  continues or exits. pthread_join provides a way to synchronize with these threads.     *
******************************************************************************************/



/*
   int pthread_create(
    pthread_t *thread,
    const pthread_attr_t *attr, -> NULL for standsrt
    void *(*start_routine)(void *), -> function to do in the new thread
    void *arg -> arg to make thread working, if no = NULL
    (in my case arg that i need PHILOSOPHERs threADs
);*/


/*int	create_thread(t_table *table, int i)
{
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &philo_routine, &table->philos[i]) != 0)
			return (-1); // + i need terninate this
		i++;
	}
	return (0);
}*/

/*
   int pthread_join(
    pthread_t thread,
    void **retval
    Указатель на указатель, который будет содержать значение, возвращённое завершившимся потоком. 
    Если функция потока возвращает значение, оно будет записано в *retval. Если вам не нужно значение, 
    вы можете передать NULL.
);*/

/*int	join_thread(t_table *table, int i)
{
	while (i < table->nb_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (-1); // + i need terninate this shit
		i++;
	}
	return (0);
}*/

int	ft_start_threads(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &philo_routine, &table->philos[i]) != 0)
			return (1); //mistake
		i++;
	}
	return (0);
}

int	ft_join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (1); //mistake
		i++;
	}
	return (0);
}
