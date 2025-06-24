/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:42:27 by trpham            #+#    #+#             */
/*   Updated: 2025/06/24 17:23:12 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_table	*table;
	
	if (ac == 1)
	{
		print_error("Please input arguments");
		return (EXIT_FAILURE);
	}
	table = malloc(sizeof(t_table));
	if (!table)
		return (EXIT_FAILURE);
	init_table(table); // recheck the return type of this func
	if (process_input(av, table) == FALSE)
	{
		free(table);
		return (EXIT_FAILURE);
	}
	// printf("input validated \n"); //db
	init_philo(table); // recheck the return type of this func
	if (start_dinner(table) == FALSE)
	{
		free(table);
		return (EXIT_FAILURE);
	}
	destroy(table);
	return (EXIT_SUCCESS);
}

int	process_input(char **av, t_table *table)
{
	char	**input_arr = NULL;
	
	input_arr = split_input(av);
	if (!input_arr)
		return (FALSE);
	// print_array(input_arr);
	if (validate_input(input_arr, table) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	start_dinner(t_table *table)
{
	int i;
	pthread_t	monitor;

	if (table->no_philo == 1) // handle 1 philo case, no eat, just wait to die
	{
		one_philo(table);
		return (TRUE);
	}

	if (pthread_create(&monitor, NULL, &monitor_routine, table) != TRUE)
	{
		print_error("Failed to create monitor thread");
		destroy(table); //recheck destroy func
		return (FALSE);
	}
	i = 0;
	while (i < table->no_philo)
	{
		if (pthread_create(&table->philo_table[i].thr, NULL,
			&philo_routine, (void *)&table->philo_table[i]) != TRUE)
		{
			print_error("Failed to create thread");
			destroy(table);
			return (FALSE);
		}
		i++;
	}
	if (pthread_join(monitor, NULL) != TRUE)
	{
		print_error("Failed to join monitor thread");
		destroy(table);
		return (FALSE);
	}
	i = 0;
	while (i < table->no_philo)
	{
		if (pthread_join(table->philo_table[i].thr, NULL) != TRUE) // wait for thr to finish
		{
			print_error("Failed to join thread");
			destroy(table);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void	one_philo(t_table *table)
{
	t_philo	*philo;

	philo = &table->philo_table[0];
	if (table->no_philo == 1)
	{
		thinking_routine(philo);
		pthread_mutex_lock(philo->l_fork);
		lock_and_printf(philo, "has taken a fork");
		ft_usleep(philo->time_to_die, philo);
		lock_and_printf(philo, "died");
		pthread_mutex_unlock(philo->l_fork);
	}
}