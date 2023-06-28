/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:01:31 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/06/28 20:32:12 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	die(int id, t_data *data)
{
	print_log(id, "is dead.", data);
	return (1);
}

int	take_fork(int id, t_data *data)
{
	print_log(id, "has taken a fork.", data);
	return (1);
}


int eating(int id, t_data *data) {
    if (pthread_mutex_lock(data->philo[id].l_fork) != 0) {
        printf("Error: Failed to acquire left fork for philosopher %d\n", id + 1);
        return 0;
    }
    printf("Philosopher %d has taken the left fork.\n", id + 1);
    
    if (print_log(id, "has taken a fork", data) == 0) {
        pthread_mutex_unlock(data->philo[id].l_fork);
        return 0;
    }
    
    if (pthread_mutex_lock(data->philo[id].r_fork) != 0) {
        printf("Error: Failed to acquire right fork for philosopher %d\n", id + 1);
        pthread_mutex_unlock(data->philo[id].l_fork);
        return 0;
    }
    printf("Philosopher %d has taken the right fork.\n", id + 1);
    
    if (print_log(id, "has taken a fork", data) == 0) {
        pthread_mutex_unlock(data->philo[id].l_fork);
        pthread_mutex_unlock(data->philo[id].r_fork);
        return 0;
    }
    
    if (print_log(id, "is eating", data) == 0) {
        pthread_mutex_unlock(data->philo[id].l_fork);
        pthread_mutex_unlock(data->philo[id].r_fork);
        return 0;
    }
    
    usleep(data->time_to_eat * 1000);
    
    pthread_mutex_unlock(data->philo[id].l_fork);
    pthread_mutex_unlock(data->philo[id].r_fork);
    
    printf("Philosopher %d has finished eating.\n", id + 1);
    
    return 1;
}

int	thinking(int id, t_data *data)
{
	print_log(id, "is thinking.", data);
	return (1);
}

int	sleeping(int id, t_data *data)
{
	print_log(id, "is sleeping.", data);
	usleep(data->time_to_sleep * 1000);
	return (1);
}