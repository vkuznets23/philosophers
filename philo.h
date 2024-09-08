/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viktoria <viktoria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:09:54 by viktoria          #+#    #+#             */
/*   Updated: 2024/09/08 20:11:38 by viktoria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h> 
# include <pthread.h>
# include <stdio.h>

/******************************************************************************
*                                 Structures                                  *
******************************************************************************/

typedef struct s_philo	t_philo;

//size_t is like unsigned int but safer and works on 64bits machines
//it actually might be 4 bytes and 8 bytes 
// int can be only 4 bytes
// so size_t is safer

typedef struct s_table
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		locks;
	t_philo				*philos;
	size_t				nb_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				must_eat_count;
	size_t				no_full;
	size_t				start;
	int					dead_or_full;
}	t_table;

typedef struct s_philo
{
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		*fork_r;
	pthread_t			thread;
	t_table				*table;
	size_t				id;
	size_t				lst_eating;
	size_t				no_ate;
}	t_philo;

/******************************************************************************
*                           Function Prototypes                               *
******************************************************************************/

//parsing
int		is_valid(int ac, char **av);
//int	ft_atoi(char *str);
int		ft_ctos(const char *str, size_t *result);

//init.c
int		init_table(int ac, char **av, t_table *table);

//start_threads
int		ft_join_threads(t_table *table);
int		ft_start_threads(t_table *table);
int		join_thread(t_table *table, int i);
int		create_thread(t_table *table, int i);

//philo_routine
size_t	get_time(void);
void	*philo_routine(void *arg);
void	eating_time(t_philo *philo);
int		ft_wait(size_t ms, t_table *table);
int		time_to_stop_sim(t_philo *philo);
int		ft_prnt_lock(t_philo *philo, const char *activity);
int		grab_forks(t_philo *philo);

//terminate
void	ft_terminate(t_table *table);
int		ft_usage(void);

//stop_threads
void	ft_stop_simulation(t_table *table);

#endif