/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:54:27 by trpham            #+#    #+#             */
/*   Updated: 2025/06/20 13:57:54 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *s)
{
	printf("Error :");
	if (!s)
		printf("Unknown\n");
	printf("%s\n", s);
}

void	init_philo(t_philo *philo)
{
	 
	memset(philo, 0, sizeof(t_philo));
	
	
}

void	init_table(t_table **table)
{
	memset((*table)->philo_table, 0, 200);
	
}
