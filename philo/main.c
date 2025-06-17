/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:42:27 by trpham            #+#    #+#             */
/*   Updated: 2025/06/17 17:20:26 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	if (ac < 5)
	{
		print_error("Invalid input");
		return (EXIT_FAILURE);
	}
	process_input(av);
	
	
	
	return (EXIT_SUCCESS);
}

int	process_input(char **input)
{
	t_philo	philo;
	
	validate_input(input);

	
	
	return (TRUE);
}
int	validate_input(char **input)
{
	(void)*input;

	
	return (TRUE);
}


void	init_philo(t_philo *philo)
{
	memset(philo, 0, sizeof(t_philo));
	
}
void	*routin()
{
	printf("printing\n");
	sleep(3);
	printf("test\n");
}

void	*eat_routin(void)
{
	pthread_t t1;
	pthread_t t2;

	if (pthread_create(&t1, NULL, &routin, NULL)) //return 0 if success
		return (EXIT_FAILURE);
	pthread_create(&t2, NULL, &routin, NULL);
	if (pthread_join(t1, NULL) != 0)
		return (EXIT_FAILURE);
	pthread_join(t2, NULL);
}

