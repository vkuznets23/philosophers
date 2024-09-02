#ifndef PHILO_H
# define PHILO_H

#include <limits.h>
#include <pthread.h> // for threads
#include <stdlib.h> //so far for exits
#include <stdio.h> // so fat for printf

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
	size_t	nb_philos;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	must_eat_count;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*locks;

}	t_table;

typedef struct s_philo
{
	pthread_t			thread;//kinda auto assigned 
	size_t		id;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		*fork_r;
	t_table				*table;
}	t_philo;


/******************************************************************************
*                           Function Prototypes                               *
******************************************************************************/

//parsing
int	is_valid(int ac, char **av);
int	ft_atoi(char *str);

//init.c
int	init_table(int ac, char **av, t_table *table);

//start_threads
int	ft_join_threads(t_table *table);
int	ft_create_threads(t_table *table);
int	join_thread(t_table *table, int i);
int	create_thread(t_table *table, int i);

#endif
