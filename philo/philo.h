/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:39:45 by trpham            #+#    #+#             */
/*   Updated: 2025/06/20 14:05:09 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h> //for thread
# include <string.h> // for memset

# define TRUE 0
# define FALSE -1

typedef struct s_philo
{
	int		i;
	long	last_meal_time;
	long	time_to_eat;
	long	time_to_die;
	long	time_to_sleep;
}	t_philo;

typedef	struct s_table
{
	pthread_t	philo_table[200];
	int			size;
	
}	t_table;


int	process_input(char **input, t_table **table);
int		validate_input(char **input, t_table **s_table);
void	init_game(t_table *table);


/* Helper function */
void	print_error(char *s);
void	init_table(t_table **table);
void	init_philo(t_philo *philo);

void	*routin(pthread_mutex_t *mutex);

# endif