/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:27:42 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/09/01 18:19:28 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_threads(t_vault *vault)
{
	int	i;

	i = 0;
	vault->time = get_time();
	while (i < vault->input.n_philos)
	{
		vault->thread_id = i;
		if (pthread_create(&vault->philos[i].thread,
				NULL, &process, (void *) vault) != 0)
			return (0);
		usleep(10);
		i++;
	}
	if (pthread_create(&vault->monitor, NULL,
			&threads_checker, (void *) vault) != 0)
		return (0);
	philo_wait(1);
	return (join_threads(vault));
}

int	join_threads(t_vault *vault)
{
	int	i;

	i = 0;
	while (i < vault->input.n_philos)
	{
		if (pthread_join(vault->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_join(vault->monitor, NULL) != 0)
		return (0);
	return (1);
}

void	philo_free(t_vault *vault)
{
	free(vault->philos);
	free(vault->forks);
}

int	destroy_and_free(t_vault *vault)
{
	int	i;

	i = 0;
	while (i < vault->input.n_philos)
	{
		pthread_mutex_destroy(&(vault->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&vault->read_dead);
	pthread_mutex_destroy(&vault->output);
	philo_free(vault);
	return (1);
}
