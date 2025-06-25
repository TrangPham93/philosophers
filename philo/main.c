/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:42:27 by trpham            #+#    #+#             */
/*   Updated: 2025/06/25 16:24:10 by trpham           ###   ########.fr       */
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
	free(table);
	return (EXIT_SUCCESS);
}

int	handle_thread_failed(t_table *table, int i)
{
	print_error("Create thread failed\n");
	while (--i >= 0)
	{
		if (pthread_join(table->philo_table[i].thr, NULL) != TRUE) // wait for thr to finish
		{
			print_error("Failed to join thread");
			destroy(table);
			return (FALSE);
		}
	}
	destroy(table);
	return (FALSE);
}

int	start_dinner(t_table *table)
{
	int i;
	pthread_t	monitor;

	i = -1;
	table->start_time = get_current_time();
	if (pthread_create(&monitor, NULL, &monitor_routine, table) != TRUE)
	{
		print_error("Failed to create monitor thread");
		destroy(table); //recheck destroy func
		return (FALSE);
	}
	while (++i < table->no_philo)
	{
		if (pthread_create(&table->philo_table[i].thr, NULL,
			&philo_routine, (void *)&table->philo_table[i]) != TRUE)
			{
				// destroy(table);
				return (handle_thread_failed(table, i));
			}
	}
	
	if (pthread_join(monitor, NULL) != TRUE)
	{
		print_error("Failed to join monitor thread");
		destroy(table);
		return (FALSE);
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
