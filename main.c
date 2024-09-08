/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viktoria <viktoria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:09:29 by viktoria          #+#    #+#             */
/*   Updated: 2024/09/08 19:50:29 by viktoria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		return (ft_usage());
	if (is_valid(ac, av))
		return (ft_usage());
	if (init_table(ac, av, &table) != 0)
		return (-1);
	if (ft_start_threads(&table))
	{
		ft_terminate(&table); // Properly free resources on failure
		return (-1);
	}
	ft_stop_simulation(&table);
	if (ft_join_threads(&table))
	{
		ft_terminate(&table); // Properly free resources on failure
		return (-1);
	}
	ft_terminate(&table);
	return (0);
}
