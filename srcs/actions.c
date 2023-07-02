/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:01:31 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/07/02 19:51:07 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// int	die(int id, t_data *data)
// {
//     pthread_mutex_lock(&data->write);
// 	print_log("is dead.", data);
//     pthread_mutex_unlock(&data->write);
// 	return (0);
// }

// int	take_fork(int id, t_data *data)
// {
//     pthread_mutex_lock(&data->write);
// 	print_log(id, "has taken a fork.", data);
//     pthread_mutex_unlock(&data->write);
//     return (0);
// }

void	sleeping(t_philo *philo)
{
    print_log("is sleeping", philo);
    usleep(philo->data->time_to_sleep * 1000);
}

void	eating(t_philo *philo)
{
    pthread_mutex_lock(philo->l_fork);
    print_log("has taken a fork", philo);
    pthread_mutex_lock(philo->r_fork);
    print_log("has taken a fork", philo);
    pthread_mutex_lock(&philo->lock);
    print_log("is eating", philo);
    philo->eat_count++;
    philo->lifetime = current_time() + philo->data->time_to_die;
    usleep(philo->data->time_to_eat * 1000);
    pthread_mutex_unlock(&philo->lock);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
    sleeping(philo);
}
