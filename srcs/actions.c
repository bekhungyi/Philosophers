/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:01:31 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/06/29 19:20:47 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	die(int id, t_data *data)
{
    pthread_mutex_lock(&data->write);
	print_log(id, "is dead.", data);
    pthread_mutex_unlock(&data->write);
	return (0);
}

int	take_fork(int id, t_data *data)
{
    pthread_mutex_lock(&data->write);
	print_log(id, "has taken a fork.", data);
    pthread_mutex_unlock(&data->write);
    return (0);
}

int eating(t_philo *philo)
{
    pthread_mutex_lock(philo->l_fork);
    print_log(philo->id, "has taken a fork.", philo->data);
    pthread_mutex_lock(philo->r_fork);
    print_log(philo->id, "has taken a fork.", philo->data);
    pthread_mutex_lock(&philo->lock);
    print_log(philo->id, "is eating.", philo->data);
    philo->eat_count++;
    philo->last_eat = current_time();
    philo->lifetime = philo->data->time_to_die + current_time();
    usleep(philo->data->time_to_eat * 1000);
    pthread_mutex_unlock(&philo->lock);
    pthread_mutex_lock(philo->l_fork);
    pthread_mutex_lock(philo->r_fork);
    sleeping(philo->id, philo->data);
    return (0);
}

int	thinking(int id, t_data *data)
{
	print_log(id, "is thinking.", data);
	return (0);
}

int	sleeping(int id, t_data *data)
{
	print_log(id, "is sleeping.", data);
	usleep(data->time_to_sleep * 1000);
	return (0);
}