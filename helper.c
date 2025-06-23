/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:54:27 by trpham            #+#    #+#             */
/*   Updated: 2025/06/23 17:03:02 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *s)
{
	printf("Error: ");
	if (!s)
		printf("Unknown\n");
	printf("%s\n", s);
}

void	free_array_null(char ***array)
{
	size_t	i;

	i = 0;
	if (!array || !*array)
		return ;
	while ((*array)[i])
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
}

int	array_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

int is_even_id(int	id)
{
	if (id % 2 == 0)
		return (TRUE);
	return (FALSE);
}
