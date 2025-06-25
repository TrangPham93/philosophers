/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:28:11 by trpham            #+#    #+#             */
/*   Updated: 2025/06/25 11:54:46 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_input(char **input_arr, t_table *table)
{
	int	i;
	int	count;
	long long	*long_arr;
	
	i = 0;
	while (input_arr[i])
	{
		if (is_only_digit(input_arr[i]) == FALSE)
		{
			free_array_null(&input_arr);
			return (FALSE);
		}
		i++;
	}
	count = array_size(input_arr);
	long_arr = create_long_arr(input_arr, count);
	if (!long_arr)
	{
		free_array_null(&input_arr);
		return (FALSE);
	}
	
	if (check_input_value(long_arr, table, count) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	check_input_value(long long *long_arr, t_table *table, int count)
{
	if (long_arr[0] <= 0 || long_arr[0] > PHILOMAX)
	{
		print_error("Invalid number of philosophers");
		return (FALSE);
	}
	table->no_philo = long_arr[0];
	if (long_arr[1] <= 0 || long_arr[2] <= 0 || long_arr[3] <= 0)
	{
		print_error("Invalid input value");
		return (FALSE);
	}
	if (count == 5 && long_arr[4] <= 0)
	{
		print_error("Invalid input value");
		return (FALSE);
	}
	table->time_to_die = long_arr[1];
	table->time_to_eat = long_arr[2];
	table->time_to_sleep = long_arr[3];
	if (count == 5)
		table->meal_no = long_arr[4];
	return (TRUE);
}


long long	*create_long_arr(char **input, int count)
{
	long long	num;
	long long	*long_arr = NULL;
	int			i;

	i = 0;
	long_arr = malloc((count + 1) * sizeof(long long));
	if (!long_arr)
	{
		print_error("Malloc failed");
		return (NULL);
	}
	while (input[i])
	{
		num = ft_atoi(input[i]);
		long_arr[i] = num;
		i++;
	}
	return (long_arr);
}

char	*join_input(char **av)
{
	char	*input_join;
	int		i;

	input_join = NULL;
	i = 0;
	while (av[++i]) //start from av[1]
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
	char	**input_arr = NULL;
	char	*input_str = NULL;
	int		count;

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
