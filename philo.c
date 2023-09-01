/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:27:09 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/08/31 22:15:02 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	just_one_philo(t_vault *vault)
{
	if (pthread_mutex_init(&vault->output, NULL) != 0)
		return (0);
	vault->time = get_time();
	philo_print(vault, 0, "has taken a fork");
	philo_wait(vault->input.time_to_die);
	philo_print(vault, 0, "died");
	pthread_mutex_destroy(&vault->output);
	philo_free(vault);
	return (1);
}

int	main(int ac, char **argv)
{
	t_vault	vault;

	if (!init_input(ac, argv, &vault))
		return (0);
	if (!init_p_f(&vault))
		return (destroy_and_free(&vault));
	if (vault.input.n_philos == 1)
	{
		return (just_one_philo(&vault));
	}
	init_threads(&vault);
	return (destroy_and_free(&vault));
}
