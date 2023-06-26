/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:53:21 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/06/25 18:40:55 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_forks(t_data *data)
{
	int	i;

	i = -1;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	while (++i < data->number_of_philosophers)
		pthread_mutex_init(&data->fork[i], NULL);
	i = 0;
	data->philo[0].l_fork = &data->fork[0];
	data->philo[0].r_fork = &data->fork[data->number_of_philosophers - 1];
	while (++i < data->number_of_philosophers)
	{
		data->philo[i].l_fork = &data->fork[i];
		data->philo[i].r_fork = &data->fork[i - 1];
	}
}

void	philo_init(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philo)
		return (0);
	while (i++ < data->number_of_philosophers)
	{
		data->philo[i].id = i;
		data->philo[i].eat_count = 0;
	}
}

int	data_init(int ac, char **av, t_data *data)
{
	data->start_time = current_time();
	data->dead = 0;
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->number_of_meals = 0;
	if (ac == 6)
		data->number_of_meals = ft_atoi(av[5]);
	if (!data->number_of_philosophers || !data->time_to_die || !data->time_to_eat || !data->time_to_sleep || (ac==6 && !data->number_of_meals))
	{
		printf ("Error: Invalid arguments found.");
		return (0);
	}
	return (1);
}