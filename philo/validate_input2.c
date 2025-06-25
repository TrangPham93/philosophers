/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:41:09 by trpham            #+#    #+#             */
/*   Updated: 2025/06/25 21:49:20 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*join_input(char **av)
{
	char	*input_join;
	int		i;

	input_join = NULL;
	i = 0;
	while (av[++i])
	{
		input_join = ft_strjoin(input_join, av[i]);
		if (!input_join)
		{
			free(input_join);
			return (NULL);
		}
		input_join = ft_strjoin(input_join, " ");
		if (!input_join)
		{
			free(input_join);
			return (NULL);
		}
	}
	return (input_join);
}

char	**split_input(char **av)
{
	char	**input_arr;
	char	*input_str;
	int		count;

	input_arr = NULL;
	input_str = NULL;
	input_str = join_input(av);
	if (!input_str)
		return (NULL);
	input_arr = ft_split(input_str, ' ');
	if (!input_arr)
	{
		free(input_str);
		return (NULL);
	}
	count = array_size(input_arr);
	if (count != 4 && count != 5)
	{
		print_error("Invalid input");
		free(input_str);
		free_array_null(&input_arr);
		return (NULL);
	}
	return (input_arr);
}
