/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:25:58 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/07/10 19:12:37 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <limits.h>
#include <sys/time.h>

struct s_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				l_fork;
	int				r_fork;
	long long		lifetime;
	pthread_t		thread;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	long long		start_time;
    int				nb_of_philo;
	int				nb_of_fork;
    int				nb_of_meal;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				finish_meal;
	int				dead;
	int				tid;
	pthread_t		dead_t;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write;
}	t_data;

int eating(t_data *data, int i);
int sleeping(t_data *data, int i);
int thinking(t_data *data, int i);
int drop_forks(t_data *data, int i);

int init_input(int ac, char **av, t_data *data);
int init_philos(t_data *data);
int init_p_f(t_data *data);
int init_threads(t_data *data);

void *process(void *args);
int routine_execute(t_data *data, int i);
int philo_is_dead(t_data *data, int *i);
void *threads_checker(void *args);
int join_threads(t_data *data);
void philo_free(t_data *data);
int destroy_and_free(t_data *data);

int	ft_atoi(char *str);
long long	get_time();
int	philo_print(t_data *data, int id, char *str);
long long	delta_time(long long time);
void	philo_wait(long long time);


# endif
