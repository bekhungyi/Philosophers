/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:01:31 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/09/01 19:24:56 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_dead(t_vault *vault)
{
	int	dead;

	pthread_mutex_lock(&(vault->read_dead));
	dead = vault->dead;
	pthread_mutex_unlock(&(vault->read_dead));
	if (dead)
		return (1);
	return (0);
}

int	eating(t_vault *vault, int i)
{
	if (check_dead(vault))
		return (0);
	pthread_mutex_lock(&(vault->forks[vault->philos[i].left_fork]));
	if (check_dead(vault))
	{
		pthread_mutex_unlock(&(vault->forks[vault->philos[i].left_fork]));
		return (0);
	}
	philo_print(vault, vault->philos[i].philo_id, "has taken a fork");
	pthread_mutex_lock(&(vault->forks[vault->philos[i].right_fork]));
	if (check_dead(vault))
	{
		pthread_mutex_unlock(&(vault->forks[vault->philos[i].left_fork]));
		pthread_mutex_unlock(&(vault->forks[vault->philos[i].right_fork]));
		return (0);
	}
	philo_print(vault, vault->philos[i].philo_id, "has taken a fork");
	philo_print(vault, vault->philos[i].philo_id, "is eating");
	pthread_mutex_lock(&(vault->read_dead));
	vault->philos[i].time_last_ate = get_time();
	pthread_mutex_unlock(&(vault->read_dead));
	philo_wait(vault->input.time_to_eat);
	drop_forks(vault, i);
	return (1);
}

int	drop_forks(t_vault *vault, int i)
{
	pthread_mutex_unlock(&(vault->forks[vault->philos[i].left_fork]));
	pthread_mutex_unlock(&(vault->forks[vault->philos[i].right_fork]));
	vault->philos[i].n_ate++;
	return (1);
}
