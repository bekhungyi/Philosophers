/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:46:45 by jchu              #+#    #+#             */
/*   Updated: 2023/07/10 19:48:13 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define INT_MAX 2147483647

typedef struct s_philo
{
	int			philo_id;
	int			n_ate;
	long		time_to_die;
	int			left_fork;
	int			right_fork;
	pthread_t	thread;		
}	t_philo;

typedef struct s_vault
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				thread_id;
	int				dead;
	long long		time;
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	output;
}	t_vault;

// ACTIONS
int			eating(t_vault *vault, int i);
int			sleeping(t_vault *vault, int i);
int			thinking(t_vault *vault, int i);
int			drop_forks(t_vault *vault, int i);

// INIT_INPUT
int			check_errors(int ac, t_vault *vault);
int			init_input(int ac, char **av, t_vault *vault);

// INIT_P_F
int			init_philos(t_vault *vault);
int			init_p_f(t_vault *vault);
void		unlock_forks(t_vault *vault);

// INIT_THREADS
int			init_threads(t_vault *vault);
void		philo_free(t_vault *vault);
int			destroy_and_free(t_vault *vault);
int			join_threads(t_vault *vault);

// PHILO
int			just_one_philo(t_vault *vault);

// PROCESS
void		*process(void *args);
void		*threads_checker(void *args);
int			philo_is_dead(t_vault *vault, int *i);
int			routine_execute(t_vault *vault, int i);

// UTILS
int			ft_atoi(char *str);
long long	get_time(void);
long long	delta_time(long long time);
void		philo_wait(long long time);
int			philo_print(t_vault *vault, int id, char *action);

#endif