/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:01:31 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/07/08 01:14:32 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_log("has taken a fork", philo);
		pthread_mutex_lock(philo->l_fork);
		print_log("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_log("has taken a fork", philo);
		pthread_mutex_lock(philo->r_fork);
		print_log("has taken a fork", philo);
	}
}

void	eating(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
    print_log("is eating", philo);
    philo->lifetime = current_time() + philo->data->time_to_die;
    usleep(philo->data->time_to_eat * 1000);
    philo->eat_count++;
    philo->eating = 0;
    pthread_mutex_unlock(&philo->lock);
    pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
    print_log("is sleeping", philo);
    usleep(philo->data->time_to_sleep * 1000);
}
