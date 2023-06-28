/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:25:58 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/06/28 19:20:22 by bhung-yi         ###   ########.fr       */
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
	struct s_data	*data;
	int				id;
	int				eat_count;
	int				last_meal;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	lock;
	pthread_t	t1;
}	t_philo;

typedef struct s_data
{
	t_philo		*philo;
	long long	start_time;
    int			nb_of_philo;
	int			number_of_forks;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
    int			nb_of_meal;
	int			dead;
	int			done_eating;
	pthread_mutex_t	write;
	pthread_mutex_t	*fork;
}	t_data;

int		ft_atoi(char *str);
int		data_init(int ac, char **av, t_data *data);
void	philo_init(int ac, char **av, t_data *data);
void	fork_init(t_data *data);
int		thread_init(t_data *data);

int	print_log(int id, char *str, t_data *data);
long long	current_time();

/****	Actions	****/
int	die(int id, t_data *data);
int	take_fork(int id, t_data *data);
int	eating(int id, t_data *data);
int	thinking(int id, t_data *data);
int	sleeping(int id, t_data *data);

# endif
