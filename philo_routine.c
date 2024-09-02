
#include "philo.h"

//their routine consist of
// -eating (for eating i also need to grab a fork)
//	so i created mutexes i need to unlock forks at some point
// -sleaping
// -thinking

//i also need a time to stop to 
//	1) avoid infinity loop 
//	2)To manage system resources and prevent excessive consumption
//	


int	time_to_stop_sim(t_table *table)
{

}

int	grab_forks(t_philo *philo)
{
	// check if im still in the limit 
	//lock the left fork
	//check time limit 
	//lock the right fork
	// if any troubles unlock both of them
}
