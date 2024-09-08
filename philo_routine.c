/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viktoria <viktoria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:09:46 by viktoria          #+#    #+#             */
/*   Updated: 2024/09/08 18:09:49 by viktoria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_prnt_lock(t_philo *philo, const char *activity)
{
	pthread_mutex_lock(&philo->table->locks);
	if (philo->table->dead_or_full)
	{
		pthread_mutex_unlock(&philo->table->locks);
		return (0);
	}
	printf("%zu %zu %s\n", get_time() - philo->table->start,
		philo->id, activity);
	pthread_mutex_unlock(&philo->table->locks);
	return (1);
}

int	grab_forks(t_philo *philo)
{
	if (time_to_stop_sim(philo))
		return (0);
	pthread_mutex_lock(philo->fork_l);
	if (!ft_prnt_lock(philo, "has taken a L fork"))
	{
		pthread_mutex_unlock(philo->fork_l);
		return (0);
	}
	if (time_to_stop_sim(philo) || philo->table->nb_philos == 1)
	{
		pthread_mutex_unlock(philo->fork_l);
		return (0);
	}
	pthread_mutex_lock(philo->fork_r);
	if (!ft_prnt_lock(philo, "has taken a R fork"))
	{
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/* first i need to lock philo's state, then calculate how many of them have   */
/* already eatten. Then i take the time when philos last ate. After that show */
/* current status "eating" and simulate eating tim eusing wait.               */
/* if statement is used to calculate how many of then are full (to stop simul)*/
/* After that we need to unlock state mutax and forks mutaxes since this      */
/* phase is done.							      */
/* ************************************************************************** */

void	eating_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->locks);
	philo->no_ate++;
	philo->lst_eating = get_time();
	pthread_mutex_unlock(&philo->table->locks);
	ft_prnt_lock(philo, "is eating");
	ft_wait(philo->table->time_to_eat, philo->table);
	pthread_mutex_lock(&philo->table->locks);
	if (philo->no_ate == philo->table->must_eat_count)
		philo->table->no_full++;
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

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_wait(10, philo->table);
	while (1)
	{
		if (!grab_forks(philo))
			break ;
		eating_time(philo);
		if (!sleeping_thinking(philo))
			break ;
	}
	return (0);
}
