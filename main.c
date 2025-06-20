/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:42:27 by trpham            #+#    #+#             */
/*   Updated: 2025/06/20 14:03:24 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_table	*table;
	pthread_mutex_t	mutex;
	
	if (ac < 5)
	{
		print_error("Invalid input");
		return (EXIT_FAILURE);
	}
	init_table(&table);
	process_input(av, &table);
	
	pthread_mutex_init(&mutex, NULL);
	init_game(table);
	pthread_mutex_destroy(&mutex);
	
	return (EXIT_SUCCESS);
}

int	process_input(char **input, t_table **table)
{
	
	validate_input(input, table);
	
	
	return (TRUE);
}
int	validate_input(char **input, t_table **table)
{
	(void)*input;

	
	return (TRUE);
}

void	init_game(t_table *table)
{
	pthread_t	th[200];
	int			i;
	

	i = 0;
	while (i < table->size)
	{
		if (pthread_create(th[i++], NULL, &routin, NULL) != TRUE) //return 0 if success
		{
			print_error("Failed to create thread");
			return 1;
		}
	}
	i = 0;
	while (i < table->size)
	{
		if (pthread_join(th[i++], NULL) != TRUE)
			return 2;
	}
}

void	*routin(pthread_mutex_t *mutex)
{
	int	sum;

	sum = 0;
	pthread_mutex_lock(mutex);
	
	sum +=1;
	printf("sum : \n", sum);

	pthread_mutex_unlock(mutex);
}
