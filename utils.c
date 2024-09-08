/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viktoria <viktoria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:10:24 by viktoria          #+#    #+#             */
/*   Updated: 2024/09/08 18:10:25 by viktoria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ************************************************************************** */
/* Philosophers' routine consist of:                                          */
/* 	eating (for this they need to grab a fork)                            */
/*	sleaping                                                              */
/*	thinking                                                              */
/* ************************************************************************** */

//This function returns the current time in milliseconds
size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* ************************************************************************** */
/* This function waits for a specified number of milliseconds (ms)            */
/* while periodically checking whether the philosopher's state has changed    */
/* to "dead" or "full". If the philosopher is dead or full, it stops early    */
/*									      */
/* waiting_strt records the time when waiting began 			      */
/* while loop (get_time() - waiting_strt) < ms continually checks             */
/* how much time has passed since ft_wait began				      */
/* ************************************************************************** */

int	ft_wait(size_t ms, t_table *table)
{
	size_t	waiting_strt;
	size_t	i;

	waiting_strt = get_time();
	i = 0;
	while ((get_time() - waiting_strt) < ms)
	{
		if (i % 200 == 0)
		{
			pthread_mutex_lock(&table->locks);
			if (table->dead_or_full == 1)
			{
				pthread_mutex_unlock(&table->locks);
				return (0);
			}
			pthread_mutex_unlock(&table->locks);
		}
		usleep(500);
		i++;
	}
	return (1);
}
