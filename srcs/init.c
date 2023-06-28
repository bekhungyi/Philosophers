/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:53:21 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/06/28 20:33:52 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	fork_init(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	while (i < data->nb_of_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	i = 0;
	data->philo[0].l_fork = &data->fork[0];
	data->philo[0].r_fork = &data->fork[data->nb_of_philo - 1];
	while (++i < data->nb_of_philo)
	{
		data->philo[i].l_fork = &data->fork[i];
		data->philo[i].r_fork = &data->fork[i - 1];
	}
}

void	philo_init(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!data->philo)
		return ;
	while (i < data->nb_of_philo)
	{
		data->philo[i].id = i;
		printf("Philosopher %d initialized.\n", data->philo[i].id);
		data->philo[i].eat_count = 0;
		i++;
	}
	printf("Total philosophers initialized: %d\n", i);
}

int	data_init(int ac, char **av, t_data *data)
{
	data->start_time = current_time();
	data->dead = 0;
	data->nb_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->nb_of_meal = 0;
	if (ac == 6)
		data->nb_of_meal = ft_atoi(av[5]);
	if (!data->nb_of_philo || !data->time_to_die || !data->time_to_eat || !data->time_to_sleep || (ac==6 && !data->nb_of_meal))
	{
		printf ("Error: Invalid arguments found.");
		return (0);
	}
	printf("Number of philosophers: %d\n", data->nb_of_philo);
	return (1);
}
