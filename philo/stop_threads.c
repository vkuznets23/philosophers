/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:30:34 by vkuznets          #+#    #+#             */
/*   Updated: 2024/09/11 12:53:57 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ************************************************************************** */
/* This function checks if the simulations should stop.                       */
/*									      */
/* Its an infinity loop within we go through each of the philo (line 31)      */
/* get_time() is absolute time value; to get current time inside the          */
/* simulation we need to substract each philo's lst.eating (that's why [i]    */
/* from get_time     							      */
/* we need mutex to lock the acces to the table->dead_or_full                 */
/* ************************************************************************** */

void	ft_stop_simulation(t_table *table)
{
	size_t	i;

	while (1)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			pthread_mutex_lock(&table->locks);
			if (((get_time() - table->philos[i].lst_eating)
					>= table->time_to_die) || ((table->must_eat_count != 0)
					&& (table->no_full == table->nb_philos)))
			{
				table->dead_or_full = 1;
				if (table->no_full != table->nb_philos)
					printf("%zu %zu died\n", get_time() - table->start, i + 1);
				pthread_mutex_unlock(&table->locks);
				return ;
			}
			i++;
			pthread_mutex_unlock(&table->locks);
		}
	}
}
