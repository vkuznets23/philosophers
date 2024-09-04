
#include "philo.h"

//Check for Death
//check for fuleness 
//

void	ft_stop_simulation(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->locks);
		if ((get_time() - table->philos[i].lst_eating >= table->time_to_die)
				|| table->no_full == table->nb_philos)
		{
			table->dead_or_full = 1;
			if (table->no_full == table->nb_philos)
                		printf("Every philosopher ate %ld times\n", table->must_eat_count);
			else
				printf("%zu %ld died\n", get_time() - table->start, i + 1);
            		pthread_mutex_unlock(&table->locks);
            		return ;
		}
		i++;
            	pthread_mutex_unlock(&table->locks);
	}
}

void	ft_stop_thrds(t_table *table)
{
	while (1)
	{
		if (ft_stop_simulation(table))
			break ;
	}
}
