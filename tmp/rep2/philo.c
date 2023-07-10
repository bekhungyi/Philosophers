/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:18:39 by jchu              #+#    #+#             */
/*   Updated: 2023/07/10 19:53:28 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	destroy_and_free(t_vault *vault)
{
	int	i;

	i = 0;
	while (i < vault->n_philos)
	{
		pthread_mutex_destroy(&vault->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&vault->output);
	free(vault->philos);
	free(vault->forks);
	return (1);
}

int	just_one_philo(t_vault *vault)
{
	if (pthread_mutex_init(&vault->output, NULL) != 0)
		return (0);
	vault->time = get_time();
	philo_print(vault, 0, "has taken a fork");
	philo_wait(vault->time_to_die);
	philo_print(vault, 0, "died");
	destroy_and_free(vault);
	return (1);
}

int	main(int ac, char **argv)
{
	t_vault	vault;

	if (!init_input(ac, argv, &vault))
		return (0);
	if (!init_p_f(&vault))
		return (0);
	if (vault.n_philos == 1)
	{
		return (just_one_philo(&vault));
	}
	if (!init_threads(&vault))
		return (0);
	return (destroy_and_free(&vault));
}
