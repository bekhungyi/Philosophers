/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:19:39 by jchu              #+#    #+#             */
/*   Updated: 2023/07/10 19:50:17 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_philos(t_vault *vault)
{
	int	i;

	i = 0;
	vault->philos = malloc(sizeof(t_philo) * (vault->n_philos + 1));
	if (vault->philos == NULL)
		return (0);
	while (i < vault->n_philos)
	{
		vault->philos[i].philo_id = i;
		vault->philos[i].n_ate = 0;
		vault->philos[i].time_to_die = 0;
		vault->philos[i].left_fork = i;
		vault->philos[i].right_fork = (i + 1) % vault->n_philos;
		i++;
	}
	return (1);
}

int	init_p_f(t_vault *vault)
{
	int	i;

	if (!init_philos(vault))
		return (0);
	vault->time = get_time();
	i = 0;
	vault->forks = malloc(sizeof(pthread_mutex_t) * (
				vault->n_philos + 1));
	if (vault->forks == NULL)
		return (0);
	while (i < vault->n_philos)
	{
		if (pthread_mutex_init(&vault->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_errors(int ac, t_vault *vault)
{
	if (!vault->n_philos)
		printf("ERROR: There is a mistake in number of philosophers\n");
	if (!vault->time_to_die)
		printf("ERROR: There is a mistake in time to die\n");
	if (!vault->time_to_eat)
		printf("ERROR: There is a mistake in time to eat\n");
	if (!vault->time_to_sleep)
		printf("ERROR: There is a mistake in time to sleep\n");
	if (ac == 6 && !vault->meals_required)
		printf("ERROR: There is a mistake in number of times each \
philosopher must eat\n");
	if (!vault->n_philos || !vault->time_to_die
		|| !vault->time_to_eat || !vault->time_to_sleep
		|| (ac == 6 && !vault->meals_required))
		return (0);
	return (1);
}

int	init_input(int ac, char **av, t_vault *vault)
{
	if (ac > 4 && ac < 7)
	{
		vault->dead = 0;
		vault->n_philos = ft_atoi(av[1]);
		vault->time_to_die = ft_atoi(av[2]);
		vault->time_to_eat = ft_atoi(av[3]);
		vault->time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			vault->meals_required = ft_atoi(av[5]);
		else
			vault->meals_required = -1;
		return (check_errors(ac, vault));
	}
	printf ("ERROR: The number of argments must be 4 or 5\n");
	return (0);
}
