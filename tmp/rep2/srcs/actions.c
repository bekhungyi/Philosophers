/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:03:01 by jchu              #+#    #+#             */
/*   Updated: 2023/07/10 19:54:55 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	eating(t_vault *vault, int i)
{
	if (pthread_mutex_lock(&vault->forks[vault->philos[i].left_fork]) != 0)
		return (0);
	if (philo_print(vault, vault->philos[i].philo_id, "has taken a fork") == 0)
		return (0);
	if (pthread_mutex_lock(&vault->forks[vault->philos[i].right_fork]) != 0)
		return (0);
	if (philo_print(vault, vault->philos[i].philo_id, "has taken a fork") == 0)
		return (0);
	if (philo_print(vault, vault->philos[i].philo_id, "is eating") == 0)
		return (0);
	vault->philos[i].time_to_die = get_time();
	philo_wait(vault->time_to_eat);
	pthread_mutex_unlock(&vault->forks[vault->philos[i].left_fork]);
	pthread_mutex_unlock(&vault->forks[vault->philos[i].right_fork]);
	vault->philos[i].n_ate++;
	return (1);
}

int	sleeping(t_vault *vault, int i)
{
	if (philo_print(vault, vault->philos[i].philo_id, "is sleeping") == 0)
		return (0);
	philo_wait(vault->time_to_sleep);
	return (1);
}

int	thinking(t_vault *vault, int i)
{
	if (philo_print(vault, vault->philos[i].philo_id, "is thinking") == 0)
		return (0);
	return (1);
}

int	routine_execute(t_vault *vault, int i)
{
	if (eating(vault, i) == 0)
		return (0);
	if (vault->meals_required != vault->philos[i].n_ate)
	{
		if (sleeping(vault, i) == 0)
			return (0);
		if (thinking(vault, i) == 0)
			return (0);
	}
	return (1);
}
