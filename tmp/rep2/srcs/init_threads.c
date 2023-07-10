/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:41:08 by jchu              #+#    #+#             */
/*   Updated: 2023/07/10 19:52:24 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_threads(t_vault *vault)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&vault->output, NULL) != 0)
		return (0);
	while (i < vault->n_philos)
	{
		vault->thread_id = i;
		if (pthread_create(&vault->philos[i].thread,
				NULL, &process, (void *) vault) != 0)
			return (0);
		i++;
		philo_wait(1);
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
	while (i < vault->n_philos)
	{
		if (pthread_join(vault->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_join(vault->monitor, NULL) != 0)
		return (0);
	return (1);
}

void	*process(void *args)
{
	int		i;
	t_vault	*vault;

	vault = (t_vault *)args;
	i = vault->thread_id;
	if (vault->meals_required > 0)
	{
		while (vault->meals_required > vault->philos[i].n_ate
			&& vault->dead == 0)
			routine_execute(vault, i);
	}
	else
	{
		while (vault->dead == 0)
		{
			if (routine_execute(vault, i) == 0)
				break ;
		}
	}
	return (0);
}

int	philo_is_dead(t_vault *vault, int *i)
{
	int	time;

	if (*i == vault->n_philos)
		*i = 0;
	time = delta_time(vault->philos[*i].time_to_die);
	if (time > vault->time_to_die)
	{
		philo_print(vault, vault->philos[*i].philo_id, "died");
		vault->dead = 1;
		return (1);
	}
	i++;
	return (0);
}

void	*threads_checker(void *args)
{
	int		i;
	t_vault	*vault;

	i = 0;
	vault = (t_vault *)args;
	if (vault->meals_required > 0)
	{
		while (vault->meals_required > vault->philos[i].n_ate
			&& vault->dead == 0)
		{
			if (philo_is_dead(vault, &i) == 1)
				break ;
		}
	}
	else
	{
		while (vault->dead == 0)
		{
			if (philo_is_dead(vault, &i) == 1)
				break ;
		}
	}
	return (0);
}
