/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:53:21 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/08/31 18:08:07 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_errors(int ac, t_vault *vault)
{
	if (!vault->input.n_philos || vault->input.n_philos > 200)
		printf("ERROR: There is a mistake in number of philosophers\n");
	if (!vault->input.time_to_die || vault->input.time_to_die < 60)
		printf("ERROR: There is a mistake in time to die\n");
	if (!vault->input.time_to_eat || vault->input.time_to_eat < 60)
		printf("ERROR: There is a mistake in time to eat\n");
	if (!vault->input.time_to_sleep || vault->input.time_to_sleep < 60)
		printf("ERROR: There is a mistake in time to sleep\n");
	if (ac == 6 && !vault->input.meals_required)
		printf("ERROR: There is a mistake in number of times each \
philosopher must eat\n");
	if (!vault->input.n_philos || vault->input.n_philos > 200
		|| !vault->input.time_to_die || vault->input.time_to_die < 60
		|| !vault->input.time_to_eat || vault->input.time_to_eat < 60
		|| !vault->input.time_to_sleep || vault->input.time_to_sleep < 60
		|| (ac == 6 && !vault->input.meals_required))
		return (0);
	return (1);
}

int	init_input(int ac, char **av, t_vault *vault)
{
	if (ac > 4 && ac < 7)
	{
		vault->dead = 0;
		vault->input.n_philos = ft_atoi(av[1]);
		vault->input.time_to_die = ft_atoi(av[2]);
		vault->input.time_to_eat = ft_atoi(av[3]);
		vault->input.time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			vault->input.meals_required = ft_atoi(av[5]);
		else
			vault->input.meals_required = -1;
		return (check_errors(ac, vault));
	}
	printf ("ERROR: The number of argments must be 4 or 5\n");
	return (0);
}
