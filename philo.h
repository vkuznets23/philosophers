#ifndef PHILO_H
# define PHILO_H

#include <limits.h>
#include <unistd.h> // for usleep function
#include <sys/time.h> // for get time function
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
	pthread_mutex_t	locks;//is locked when checking or modifying the philosopher's statei
	int	dead_or_full;
	size_t	no_full;
	size_t	start;//This variable holds the time when the simulation began. It allows you to know how much time has passed since the simulation started. 
}	t_table;

typedef struct s_philo
{
	pthread_t			thread;//kinda auto assigned 
	size_t		id;
	size_t		lst_eating;
	size_t		no_ate;//?? mb need another mutex 
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
int	ft_start_threads(t_table *table);
int	join_thread(t_table *table, int i);
int	create_thread(t_table *table, int i);

//philo_routine
size_t	get_time();
int	ft_wait(size_t ms, t_table *table);
int	time_to_stop_sim(t_philo *philo);
int	ft_prnt_lock(t_philo *philo, const char *activity);
int	grab_forks(t_philo *philo);
void	eating_time(t_philo *philo);
void	*philo_routine(void *arg);

//terminate
void	ft_terminate(t_table *table);
void	ft_stop_simulation(t_table *table);

#endif
