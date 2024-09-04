
#include "philo.h"

//Check for Death
//check for fuleness 
//

int	ft_stop_simulation(t_table *table)
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
			{
				pthread_mutex_lock(&table->print_locks);
                		printf("Every philosopher ate %zu times\n", table->must_eat_count);
				pthread_mutex_unlock(&table->print_locks);
			}
			else
				ft_prnt_lock(table->philos, "died");
				//printf("%zu %ld died\n", get_time() - table->start, i + 1);
            		pthread_mutex_unlock(&table->locks);
            		return (1);
		}
		i++;
            	pthread_mutex_unlock(&table->locks);
	}
	return (0);//nobody dies
}

void	ft_stop_thrds(t_table *table)
{
	while (1)
	{
		if (ft_stop_simulation(table))
			break ;
	}
}
