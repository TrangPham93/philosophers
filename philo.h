/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:39:45 by trpham            #+#    #+#             */
/*   Updated: 2025/06/21 16:37:51 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h> //for thread
# include <string.h> // for memset

# define TRUE 0
# define FALSE -1

typedef struct s_philo
{
	pthread_t	thr;
	int			id;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	int			meal_no;
	long long	last_meal_time;
	int			dead_flag;
	pthread_mutex_t *eat_lock;
}	t_philo;

typedef	struct s_table
{
	int			size;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	int			meal_no;	
	t_philo		philo_table[200]; // need to add null and monitor?
	pthread_mutex_t	eat_lock;
}	t_table;

/* Process input */
int			process_input(char **input, t_table **table);
int			validate_input(char **input_arr, t_table **table);
int			check_input_value(long long *long_arr, t_table **table);
long long	*create_long_arr(char **input, int count);
char		**split_input(char **av);
char		*join_input(char **av);

/* Initialize table */
// void	init_game(t_table *table);
void	init_table(t_table **table);
int		init_philo(t_table **table);
// void	*routin(void *);

/* Routine */
void	*thinking_routine(void *arg);

/* Helper function */
// char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	**ft_split(char const *s, char c);
int		array_size(char **arr);
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
int		is_only_digit(char *s);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);



void	print_error(char *s);
void	free_array_null(char ***array);


/* to delete before submission */
void	print_array(char **arr);

# endif