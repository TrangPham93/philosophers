/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:42:27 by trpham            #+#    #+#             */
/*   Updated: 2025/06/21 15:41:27 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_table	*table;
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
	int	i = 0;
	while (i < table->size)
	{
		table->philo_table[i].id = i;
		table->philo_table->time_to_die = table->time_to_die;
		table->philo_table->time_to_eat = table->time_to_eat;
		table->philo_table->time_to_sleep = table->time_to_sleep;
		table->philo_table->meal_no = table->meal_no;
		
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


// void	init_game(t_table *table)
// {
// 	pthread_t	th[200];
// 	int			i;
	

// 	i = 0;
// 	while (i < table->size)
// 	{
// 		if (pthread_create(&th[i++], NULL, &routin, NULL) != TRUE) //return 0 if success
// 		{
// 			print_error("Failed to create thread");
// 			return ;
// 		}
// 	}
// 	i = 0;
// 	while (i < table->size)
// 	{
// 		if (pthread_join(th[i++], NULL) != TRUE)
// 			return ;
// 	}
// }

// void	*routin(void *)
// {
// 	int	sum;

// 	sum = 0;
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		pthread_mutex_lock(&mutex);
		
// 		sum++;
		
// 		pthread_mutex_unlock(&mutex);
		
// 	}
// 	printf("sum : %d\n", sum);
// }
