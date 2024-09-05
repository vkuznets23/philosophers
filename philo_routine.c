
#include "philo.h"

//their routine consist of
// -eating (for eating i also need to grab a fork)
//	so i created mutexes i need to unlock forks at some point
// -sleaping
// -thinking

//i also need a time to stop to 
//	1) avoid infinity loop 
//	2)To manage system resources and prevent excessive consumption
//	

//This function returns the current time in milliseconds
size_t	get_time()
{
	struct	timeval tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

//This function waits for a specified number of milliseconds (ms) 
//while periodically checking whether the philosopher's state has changed 
//to "dead" or "full". If the philosopher is dead or full, it stops waiting early.

// int pthread_mutex_lock(pthread_mutex_t *mutex);
//int pthread_mutex_unlock(pthread_mutex_t *mutex);

int	ft_wait(size_t ms, t_table *table)
{
	size_t	waiting_strt;
	size_t	i;

	waiting_strt = get_time();//records the time when the wait began
	i = 0;
	while((get_time() - waiting_strt) < ms)//continually checks how much time has passed since ft_wait began
	{
		if (i % 200 == 0)
		{
			pthread_mutex_lock(&table->locks);
			if (table->dead_or_full == 1)//true
			{
				pthread_mutex_unlock(&table->locks);//it doesnt need a fork anymore
				return (0);//stop and exit 0-because of unexpected behaviour
			}
			pthread_mutex_unlock(&table->locks);//it doesnt need a fork anymore
		}
		usleep(500);
		i++;
	}
	return (1);
}

int	time_to_stop_sim(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->locks);
	if (philo->table->dead_or_full) //1 -> true
	{
		pthread_mutex_unlock(&philo->table->locks);
		return (1); //stoping condition has been met
	}
	pthread_mutex_unlock(&philo->table->locks);
	return (0); //no stopping

}

int	ft_prnt_lock(t_philo *philo, const char *activity)
{
	pthread_mutex_lock(&philo->table->locks);
	if (philo->table->dead_or_full)
	{
		pthread_mutex_unlock(&philo->table->locks);
		return 0;
	}
	printf("%zu %zu %s\n", get_time() - philo->table->start, philo->id, activity);
	pthread_mutex_unlock(&philo->table->locks);
	return (1);
}

int	grab_forks(t_philo *philo)
{
	// check if simulation should continue
	//	i need to lock the state before checking
	//	need to check if dead_or_full is 0:
	//		if its dead (0)  simulation stops -> unlock the lock and return 1 (to signal that the stopping condition has been met)
	//		if its not tead (1) (to indicate that the stopping condition has not been met)
	//lock the left fork
	//check time 
	//lock the right fork
	// if any troubles unlock both of them

	if (time_to_stop_sim(philo))// == 1
		return (0);//we need to exit
	pthread_mutex_lock(philo->fork_l);
	if (!ft_prnt_lock(philo, "has taken a L fork"))
	{
		pthread_mutex_unlock(philo->fork_l);
		return (0);
	}
	if (time_to_stop_sim(philo) || philo->table->nb_philos == 1)// == 1 
	{
		pthread_mutex_unlock(philo->fork_l);//??????
		return (0);
	}
	pthread_mutex_lock(philo->fork_r);
	if (!ft_prnt_lock(philo, "has taken a R fork"))
	{
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		return (0);
	}
	return (1);//success
}

void	eating_time(t_philo *philo)
{
	//lock philosopher's state
	pthread_mutex_lock(&philo->table->locks);
	//Update the eating status and last time eaten
	philo->no_ate++;//calculate how many of then have eatten
	
	philo->lst_eating = get_time();
	
	//Unlock the philosopher's mutex
	pthread_mutex_unlock(&philo->table->locks);

	//display the activity of the philosopher.
	ft_prnt_lock(philo, "is eating");
	/*if (!ft_prnt_lock(philo, "is eating"))
	{
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		return ;
	}*/
	//simulate eating time using wait
	ft_wait(philo->table->time_to_eat, philo->table);
	pthread_mutex_lock(&philo->table->locks);

	if (philo->no_ate == philo->table->must_eat_count)
		philo->table->no_full++;// calculate how many of them are full

	pthread_mutex_unlock(&philo->table->locks);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

int	sleeping_thinking(t_philo *philo)
{
	if (!ft_prnt_lock(philo, "is sleeping"))
		return (0);
	if (!ft_wait(philo->table->time_to_sleep, philo->table))
		return (0);
	if (!ft_prnt_lock(philo, "is thinking"))
		return (0);
	return (1);
}


void	*philo_routine(void *arg) //it sould take my philo struct
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_wait(10, philo->table);
	while (1) 
	{
		//grabing forks
		//eating
		//sleeping or thinking
		if (!grab_forks(philo))//no success
			break ;//something goes wrong
		eating_time(philo);
		if (!sleeping_thinking(philo))
			break ;
	}
	return (0);
}
