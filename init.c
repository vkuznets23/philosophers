/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:27:37 by vkuznets          #+#    #+#             */
/*   Updated: 2024/09/09 11:36:34 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ************************************************************************** */
/*  If statement at the line 30 checkes if i need clean up mutexes and        */
/*  free space								      */
/* ************************************************************************** */

int	init_forks(t_table *table)
{
	size_t	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!table->forks)
		return (1);
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&table->forks[--i]);
			free(table->forks);
			return (1);
		}
		i++;
	}
	return (0);
}
/* ************************************************************************** */
/* Each philosopher has a number ranging from 1 to number_of_philosophers     */
/* that's why we need i + 1 (since i == 0)				      */
/* ************************************************************************** */

int	init_philosophers(t_table *table)
{
	size_t	i;

	table->philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (!table->philos)
		return (1);
	i = 0;
	while (i < table->nb_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].no_ate = 0;
		table->philos[i].fork_l = &table->forks[i];
		table->philos[i].fork_r = &table->forks[(i + 1) % table->nb_philos];
		table->philos[i].lst_eating = table->start;
		i++;
	}
	return (0);
}

// Initialize the mutexes for the table's state and printing
int	init_table_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->locks, NULL) != 0)
		return (1);
	return (0);
}

/* ************************************************************************** */
/* init_table:   							      */
/* Initializes the "dining table", the data structure containing all of       */
/* the program's parameters. Returns a pointer to the allocated table         */
/* structure, or NULL if an error occured during initialization.              */
/* ************************************************************************** */

static int	init_table_arguments(int ac, char **av, t_table *table)
{
	if (ft_ctos(av[1], &table->nb_philos))
		return (ft_usage());
	if (ft_ctos(av[2], &table->time_to_die))
		return (ft_usage());
	if (ft_ctos(av[3], &table->time_to_eat))
		return (ft_usage());
	if (ft_ctos(av[4], &table->time_to_sleep))
		return (ft_usage());
	table->must_eat_count = 0;
	table->no_full = 0;
	table->dead_or_full = 0;
	table->start = get_time();
	if (ac == 6)
		if (ft_ctos(av[5], &table->must_eat_count))
			return (ft_usage());
	return (0);
}

int	init_table(int ac, char **av, t_table *table)
{
	size_t	i;

	i = 0;
	if (init_table_arguments(ac, av, table) != 0)
		return (1);
	if (init_forks(table) != 0)
		return (1);
	if (init_philosophers(table) != 0)
	{
		while (i < table->nb_philos)
			pthread_mutex_destroy(&table->forks[i++]);
		free(table->forks);
		return (1);
	}
	if (init_table_mutexes(table) != 0)
	{
		ft_terminate(table);
		return (1);
	}
	return (0);
}
