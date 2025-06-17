/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:39:45 by trpham            #+#    #+#             */
/*   Updated: 2025/06/17 17:19:32 by trpham           ###   ########.fr       */
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

int	process_input(char **input);
int	validate_input(char **input);

/* Helper function */
void	print_error(char *s);

# endif