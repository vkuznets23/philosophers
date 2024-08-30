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

typedef struct s_table
{
	time_t time_to_die;
	time_t time_to_eat;
	time_t time_to_sleep;
	int		must_eat_count;
	unsigned int	nb_philos;
	t_philo			**philos;

}	t_table;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		fork[2];//array for L and R one
}	t_philo;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
}	t_status;

/******************************************************************************
*                           Function Prototypes                               *
******************************************************************************/

bool	is_valid(int ac, char **av);

#endif
