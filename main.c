/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:42:27 by trpham            #+#    #+#             */
/*   Updated: 2025/06/25 12:45:24 by trpham           ###   ########.fr       */
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
	if (init_table(table) == FALSE) // recheck the return type of this func
		return (EXIT_FAILURE);
	if (process_input(av, table) == FALSE)
	{
		free(table);
		return (EXIT_FAILURE);
	}
	init_philo(table); // recheck the return type of this func
	if (init_forks(table) == FALSE)
		return (EXIT_FAILURE);
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
	if (validate_input(input_arr, table) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	handle_thread_failed(t_table *table, int i)
{
	int	j;

	j = -1;
	print_error("Create thread failed");
	while (++j < i)
	{
		if (pthread_join(table->philo_table[j].thr, NULL) != TRUE) // wait for thr to finish
		{
			print_error("Failed to join thread");
			destroy(table);
			return (FALSE);
		}
	}
	return (FALSE);
}

int	start_dinner(t_table *table)
{
	int i;
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &monitor_routine, table) != TRUE)
	{
		print_error("Failed to create monitor thread");
		destroy(table); //recheck destroy func
		return (FALSE);
	}
	i = -1;
	while (++i < table->no_philo)
	{
		if (pthread_create(&table->philo_table[i].thr, NULL,
			&philo_routine, (void *)&table->philo_table[i]) != TRUE)
		{
			print_error("Failed to create thread");
			destroy(table);
			return (handle_thread_failed(table, i));
		}
	}
	if (pthread_join(monitor, NULL) != TRUE)
	{
		print_error("Failed to join monitor thread");
		destroy(table);
		return (handle_thread_failed(table, i));
	}
	i = -1;
	while (++i < table->no_philo)
	{
		if (pthread_join(table->philo_table[i].thr, NULL) != TRUE) // wait for thr to finish
		{
			print_error("Failed to join thread");
			destroy(table);
			return (FALSE);
		}
	}
	return (TRUE);
}
