#ifndef PHILO_H
# define PHILO_H

#include <stdbool.h>
#include <limits.h>
#include <time.h> // for time_t
#include <pthread.h> // for threads
#include <stdlib.h> //so far for exits
#include <stdio.h> // so fat for printf

/******************************************************************************
*                                 Structures                                  *
******************************************************************************/

typedef struct s_philo	t_philo;

//int?? or unsigned int or size_t

typedef struct s_table
{
	unsigned int	nb_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_count;
	t_philo			**philos;
	pthread_mutex_t	*forks;

}	t_table;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		fork[2];//array for L and R one
	t_table				*table;
}	t_philo;


/******************************************************************************
*                           Function Prototypes                               *
******************************************************************************/

//parsing
bool	is_valid(int ac, char **av);
int	ft_atoi(char *str);

#endif
