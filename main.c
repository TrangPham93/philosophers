/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:42:27 by trpham            #+#    #+#             */
/*   Updated: 2025/06/23 16:35:18 by trpham           ###   ########.fr       */
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
	init_table(&table);
	if (process_input(av, &table) == FALSE)
	{
		free(table);
		return (EXIT_FAILURE);
	}
	// printf("input validated \n"); //db
	if (init_philo(&table) == FALSE) // recheck the return type of this func
	{
		free(table);
		return (EXIT_FAILURE);
	}
	if (start_dinner(&table) == FALSE)
	{
		free(table);
		return (EXIT_FAILURE);
	}
	destroy(&table);
	return (EXIT_SUCCESS);
}

int	process_input(char **av, t_table **table)
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

int	start_dinner(t_table **table)
{
	int i;

	i = 0;
	while (i < (*table)->size)
	{
		if (pthread_create(&(*table)->philo_table[i].thr, NULL,
			&philo_routine, (void *)&(*table)->philo_table[i]) != TRUE) // create philo thr
		{
			print_error("Failed to create thread");
			return (FALSE);
		}
		i++;
	}
	i = 0;
	while (i < (*table)->size)
	{
		if (pthread_join((*table)->philo_table[i++].thr, NULL) != TRUE) // wait for thr to finish
		{
			print_error("Failed to join thread");
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

