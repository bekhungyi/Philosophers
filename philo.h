/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:25:58 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/06/25 18:28:45 by bhung-yi         ###   ########.fr       */
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

typedef struct s_philo
{
	int				id;
	int				eat_count;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

typedef struct s_data
{
	t_philo		*philo;
	long long	start_time;
    int			number_of_philosophers;
	int			number_of_forks;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
    int			number_of_meals;
	int			dead;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*fork;
}	t_data;

int		ft_atoi(char *str);
int		data_init(int ac, char **av, t_data *data);

void	print_log(int id, char *str, t_data *data);
long long	current_time();

/****	Actions	****/
int	die(int id, t_data *data);
int	take_fork(int id, t_data *data);
int	eating(int id, t_data *data);
int	thinking(int id, t_data *data);
int	sleeping(int id, t_data *data);

# endif
