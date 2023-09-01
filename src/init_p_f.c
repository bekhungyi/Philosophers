/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_p_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:53:23 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/08/31 22:17:40 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_philo(t_vault *vault)
{
	int	i;

	i = 0;
	vault->philos = malloc(sizeof(t_philo) * (vault->input.n_philos + 1));
	if (vault->philos == NULL)
		return (0);
	while (i < vault->input.n_philos)
	{
		vault->philos[i].philo_id = i;
		vault->philos[i].n_ate = 0;
		vault->philos[i].time_last_ate = 0;
		vault->philos[i].left_fork = i;
		vault->philos[i].right_fork = (i + 1) % vault->input.n_philos;
		i++;
	}
	return (1);
}

int	init_p_f(t_vault *vault)
{
	int	i;

	i = 0;
	pthread_mutex_init(&vault->output, NULL);
	pthread_mutex_init(&vault->read_dead, NULL);
	if (!init_philo(vault))
		return (0);
	vault->forks = malloc(sizeof(pthread_mutex_t) * (
				vault->input.n_philos + 1));
	if (vault->forks == NULL)
		return (0);
	while (i < vault->input.n_philos)
	{
		if (pthread_mutex_init(&vault->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}
