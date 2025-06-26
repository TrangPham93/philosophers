/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:42:27 by trpham            #+#    #+#             */
/*   Updated: 2025/06/26 16:24:43 by trpham           ###   ########.fr       */
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
	{
		print_error("Mutex init failed");
		free(table);
		return (EXIT_FAILURE);
	}
	if (process_input(av, table) == FALSE)
	{
		free(table);
		return (EXIT_FAILURE);
	}
	init_philo(table); // recheck the return type of this func
	if (init_forks(table) == FALSE)
	{
		print_error("Forks init failed");
		pthread_mutex_destroy(&table->write_lock);
		pthread_mutex_destroy(&table->dead_lock);
		pthread_mutex_destroy(&table->meal_lock);
		free(table);
		return (EXIT_FAILURE);
	}
	if (start_dinner(table) == FALSE)
	{
		free(table);
		return (EXIT_FAILURE);
	}
	free(table);
	return (EXIT_SUCCESS);
}

int	start_dinner(t_table *table)
{
	int	i;

	table->start_time = get_current_time();
	i = -1;
	while (++i < table->no_philo)
		table->philo_table[i].last_meal_time = table->start_time;
	
	if (create_philos_thread(table) == FALSE)
		return (FALSE);

	// while (1)
	// {
	// 	if (monitor_routine(table) == FALSE)
	// 		break;
	// }
		
	if (monitor_routine(table) == FALSE)
	{
		// printf("inside monitor failure\n");
		i = -1;
		while (++i < table->no_philo)
		{
			pthread_join(table->philo_table[i].thr, NULL);
			// printf("joined philo %d\n", i);
		}
		destroy(table);
		return (FALSE);
	}

	i = -1;
	while (++i < table->no_philo)
	{
		pthread_join(table->philo_table[i].thr, NULL);
	}
	destroy(table);
	return (TRUE);
}

int	create_philos_thread(t_table *table)
{
	int	i;
	
	i = -1;
	while (++i < table->no_philo)
	{
		if (pthread_create(&table->philo_table[i].thr, NULL,
				&philo_routine, (void *)&table->philo_table[i]) != 0)
		{
			pthread_mutex_lock(&table->dead_lock);
			table->dead_flag = TRUE;
			pthread_mutex_unlock(&table->dead_lock);
			pthread_mutex_lock(&table->write_lock);
			print_error("Create thread failed\n");
			pthread_mutex_unlock(&table->write_lock);
			while (--i >= 0)
			{
				pthread_join(table->philo_table[i].thr, NULL); // wait for thr to finish
			}
			destroy(table);
			return (FALSE);
		}
	}
	return (TRUE);
}
