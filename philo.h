/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:25:58 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/06/18 16:25:20 by bhung-yi         ###   ########.fr       */
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
    int				left_fork;
    int				right_fork;
    int				eat_count;
    pthread_mutex_t	*forks;
    pthread_mutex_t	*print;
    pthread_mutex_t	*eat;
}	t_philo;

typedef struct s_data
{
	long long	start_time;
    int			number_of_philosophers;
	int			number_of_forks;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
}	t_data;

int		ft_atoi(char *str);
void	av_init(int ac, char **av, t_data *data);

void	print_log(int id, char *str, t_data *data);
long long	current_time();

/****	Actions	****/
int	die(int id, t_data *data);
int	eating(int id, t_data *data);
int	thinking(int id, t_data *data);
int	sleeping(int id, t_data *data);

# endif
