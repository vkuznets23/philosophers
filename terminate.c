/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viktoria <viktoria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:10:13 by viktoria          #+#    #+#             */
/*   Updated: 2024/09/08 19:50:32 by viktoria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ************************************************************************** */
/* This function terminate whole process:                                     */
/* 	destroy all fork mutexes and general mutex			      */
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

int	time_to_stop_sim(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->locks);
	if (philo->table->dead_or_full)
	{
		pthread_mutex_unlock(&philo->table->locks);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->locks);
	return (0);
}

int	ft_usage(void)
{
	printf("./philo <num_philo> <die> <eat> <sleep> [must_eat]\n");
	printf("num_philo           > 0     (required)\n");
	printf("die                 > 0     (ms, required)\n");
	printf("eat                 > 0     (ms, required)\n");
	printf("sleep               > 0     (ms, required)\n");
	printf("must_eat            > 0     (optional)\n");
	return (1);
}
