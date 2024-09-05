
#include "philo.h"

//Check for Death
//check for fuleness 
//

void	ft_stop_simulation(t_table *table)
{
	size_t 	i;

	while (1)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			pthread_mutex_lock(&table->locks);

			//because get_time() is absolute current time
			if (((get_time() - table->philos[i].lst_eating) >= (size_t)table->time_to_die)
				|| ((table->must_eat_count != 0) && (table->no_full == table->nb_philos)))
			{
				table->dead_or_full = 1;
				pthread_mutex_unlock(&table->locks);
				ft_prnt_lock(table->philos, "dead or full");
				return ;
			}
			i++;
			pthread_mutex_unlock(&table->locks);
		}
	}
}

/*void	ft_stop_simulation(t_table *table)
{
	size_t	i;

	i = 0;
	while (1)
	{
		while (i < table->nb_philos)
		{
			pthread_mutex_lock(&table->locks);
			if (get_time() >= table->time_to_die)
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
            			pthread_mutex_unlock(&table->locks);
            			break ;
			}
			i++;
            		pthread_mutex_unlock(&table->locks);
		}
	}
}*/
