/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:01:31 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/07/10 18:59:40 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int eating(t_data *data, int i)
{
	if (pthread_mutex_lock(&data->fork[data->philo[i].l_fork]) != 0)
		return 0;
	if (philo_print(data, data->philo[i].id, "has taken a fork") == 0)
		return 0;
	if (pthread_mutex_lock(&data->fork[data->philo[i].r_fork]) != 0)
		return 0;
	if (philo_print(data, data->philo[i].id, "has taken a fork") == 0)
		return 0;
	if (philo_print(data, data->philo[i].id, "is eating") == 0)
		return 0;
	data->philo[i].lifetime = get_time();
	philo_wait(data->time_to_eat);
	drop_forks(data, i);
	return 1;
}

int sleeping(t_data *data, int i)
{
	if (philo_print(data, data->philo[i].id, "is sleeping") == 0)
		return 0;
	philo_wait(data->time_to_sleep);
	return 1;
}

int thinking(t_data *data, int i)
{
	if (philo_print(data, data->philo[i].id, "is thinking") == 0)
		return 0;
	return 1;
}

int drop_forks(t_data *data, int i)
{
	if (pthread_mutex_unlock(&data->fork[data->philo[i].l_fork]) != 0)
		return 0;
	if (pthread_mutex_unlock(&data->fork[data->philo[i].r_fork]) != 0)
		return 0;
	data->philo[i].eat_count++;
	return 1;
}