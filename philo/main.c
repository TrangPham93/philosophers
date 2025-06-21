/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:42:27 by trpham            #+#    #+#             */
/*   Updated: 2025/06/21 16:32:46 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_table	*table;
	int i;
	// pthread_mutex_t	mutex;
	
	if (ac == 1)
	{
		print_error("Please input arguments");
		return (EXIT_FAILURE);
	}
	table = malloc(sizeof(t_table));
	if (!table)
		return (EXIT_FAILURE);
	init_table(&table);
	if (process_input(av, &table) == FALSE)
		return (EXIT_FAILURE);
	printf("input validated \n"); //db
	if (init_philo(&table) == FALSE)
		return (EXIT_FAILURE);
	i = 0;
	while (i < table->size)
	{
		if (pthread_join(table->philo_table[i++].thr, NULL) != TRUE)
		{
			print_error("Failed to join thread");
			return (EXIT_FAILURE);
		}
	}

		// pthread_mutex_init(&mutex, NULL);
	// init_game(table);
	// pthread_mutex_destroy(&mutex);
	
	return (EXIT_SUCCESS);
}

int	process_input(char **av, t_table **table)
{
	char	**input_arr;
	
	input_arr = split_input(av);
	if (!input_arr)
		return (FALSE);
	// print_array(input_arr);
	
	if (validate_input(input_arr, table) == FALSE)
		return (FALSE);
	return (TRUE);
}
