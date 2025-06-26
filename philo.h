/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:39:45 by trpham            #+#    #+#             */
/*   Updated: 2025/06/26 16:37:53 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h> // usleep
# include <limits.h>
# include <pthread.h> //for thread
# include <string.h> // for memset
# include <sys/time.h> //gettimeofday

# define TRUE 0
# define FALSE -1
# define PHILOMAX 500

typedef struct s_philo
{
	pthread_t		thr;
	int				id;
	long long		last_meal_time;
	int				meal_eaten;
	int				is_holding_left_f;
	int				is_holding_right_f;
	pthread_mutex_t	*l_fork; //recurssive?
	pthread_mutex_t	*r_fork;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				no_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	int				meal_no;
	int				dead_flag;
	int				all_philos_eat;
	t_philo			philo_table[PHILOMAX];
	pthread_mutex_t	forks[PHILOMAX];
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
}	t_table;

/* Process input */
int			process_input(char **input, t_table *table);
int			validate_input(char **input_arr, t_table *table);
int			check_input_value(long long *long_arr, t_table *table, int count);
long long	*create_long_arr(char **input, int count);
char		**split_input(char **av);
char		*join_input(char **av);
int			check_invalid(t_table *table, int count);

/* Initialize table */
int			init_table(t_table *table);
void		init_philo(t_table *table);
int			init_forks(t_table *table);
int			start_dinner(t_table *table);

/* Routine */
void		*philo_routine(void *arg);
void		thinking_routine(t_philo *philo);
void		sleeping_routine(t_philo *philo);
int			eating_routine(t_philo *philo);
int			get_dead_flag(t_philo *philo);
int	create_philos_thread(t_table *table);
// void		handle_thread_failed(t_table *table, int i);
int	odd_lock_fork(t_philo *philo);
// void	odd_lock_fork(t_philo *philo);
// void	even_lock_fork(t_philo *philo);
// void		lock_left_fork(t_philo *philo);
// void		lock_right_fork(t_philo *philo);
void		unlock_fork(t_philo *philo);

/* Monitor */
int		monitor_routine(t_table *table);
int			one_philo_die(t_table *table);
int			all_philos_eat(t_table *table);

// Suspend execution for millisecond intervals
int			ft_usleep(long long milliseconds, t_philo *philo);

// Get current time (second and microsecond) in milliseconds.
long long	get_current_time(void);

/* Helper function */
char		*ft_strjoin(char const *s1, char const *s2);
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		**ft_split(char const *s, char c);
int			array_size(char **arr);
int			ft_atoi(const char *nptr);
int			ft_isdigit(int c);
int			is_only_digit(char *s);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			is_even_id(int id);
void		print_error(char *s);
void		lock_and_printf(t_philo *philo, char *msg);
void		lock_and_print_death(t_philo *philo);

/* Free memory */
void		free_array_null(char ***array);
void		destroy(t_table *table);

/* to delete before submission */
void		print_array(char **arr);
// void		lock_and_print_msg(t_philo *philo, const char *format, int val);
void lock_and_print_msg(t_philo *philo, const char *format);
void		print_long_array(long long *arr);

#endif