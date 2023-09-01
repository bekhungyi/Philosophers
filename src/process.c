/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:53:25 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/08/31 21:51:08 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*process(void *args)
{
	int		i;
	t_vault	*vault;

	vault = (t_vault *)args;
	i = vault->thread_id;
	if (i % 2 != 0)
		philo_wait(1);
	if (vault->input.meals_required > 0)
	{
		while (vault->input.meals_required > vault->philos[i].n_ate
			&& !check_dead(vault))
		{
			if (routine_execute(vault, i) == 0)
				break ;
		}
	}
	else
	{
		while (!check_dead(vault))
		{
			if (routine_execute(vault, i) == 0)
				break ;
		}
	}
	return (0);
}

int	routine_execute(t_vault *vault, int i)
{
	if (eating(vault, i) == 0)
		return (0);
	if (vault->input.meals_required != vault->philos[i].n_ate)
	{
		if (check_dead(vault))
			return (0);
		philo_print(vault, vault->philos[i].philo_id, "is sleeping");
		philo_wait(vault->input.time_to_sleep);
		if (check_dead(vault))
			return (0);
		philo_print(vault, vault->philos[i].philo_id, "is thinking");
	}
	return (1);
}

int	philo_is_dead(t_vault *vault, int *i)
{
	int	time_after_last_ate;

	if (*i == vault->input.n_philos)
		*i = 0;
	time_after_last_ate = delta_time(vault->philos[*i].time_last_ate);
	if (time_after_last_ate > vault->input.time_to_die)
	{
		philo_print(vault, vault->philos[*i].philo_id, "died");
		pthread_mutex_lock(&(vault->read_dead));
		vault->dead = 1;
		pthread_mutex_unlock(&(vault->read_dead));
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
	if (vault->input.meals_required > 0)
	{
		while (vault->input.meals_required > vault->philos[i].n_ate
			&& !check_dead(vault))
		{
			if (philo_is_dead(vault, &i) == 1)
				break ;
		}
	}
	else
	{
		while (!check_dead(vault))
		{
			if (philo_is_dead(vault, &i) == 1)
				break ;
		}
	}
	return (0);
}
