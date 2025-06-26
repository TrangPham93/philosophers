/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:41:09 by trpham            #+#    #+#             */
/*   Updated: 2025/06/26 17:57:30 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_input(char **av, char **input_join)
{
	char	*temp;
	int		i;

	i = 0;
	while (av[++i])
	{
		temp = *input_join;
		*input_join = ft_strjoin(*input_join, av[i]);
		if (!*input_join)
		{
			free(temp);
			return (FALSE);
		}
		free(temp);
		temp = *input_join;
		*input_join = ft_strjoin(*input_join, " ");
		if (!*input_join)
		{
			free(temp);
			return (FALSE);
		}
		free(temp);
	}
	return (TRUE);
}

char	**split_input(char **av)
{
	char	**input_arr;
	char	*input_str;
	int		count;

	input_arr = NULL;
	input_str = NULL;
	if (join_input(av, &input_str) == FALSE)
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
	free(input_str);
	return (input_arr);
}
