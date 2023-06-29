/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:53:21 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/06/29 18:08:29 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	fork_init(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->fork)
		return ;
	while (i < data->nb_of_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	data->philo[0].l_fork = &data->fork[0];
	data->philo[0].r_fork = &data->fork[data->nb_of_philo - 1];
	i = 1;
	while (i < data->nb_of_philo)
	{
		data->philo[i].l_fork = &data->fork[i];
		data->philo[i].r_fork = &data->fork[i - 1];
		i++;
	}
}

void	philo_init(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!data->philo)
		return ;
	while (i < data->nb_of_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].last_eat = data->start_time;
		data->philo[i].lifetime = data->time_to_die + data->start_time;
		pthread_mutex_init(&data->philo[i].lock, NULL);
		i++;
	}
	fork_init(data);
}

int	data_init(int ac, char **av, t_data *data)
{
	data->start_time = current_time();
	data->nb_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->nb_of_meal = 0;
	data->finish_meal = 0;
	data->dead = 0;
	if (ac == 6)
		data->nb_of_meal = ft_atoi(av[5]);
	data->tid = malloc(sizeof(pthread_t) * data->nb_of_philo);
	if (!data->tid)
		return (1);
	pthread_mutex_init(&data->write, NULL);
    philo_init(data);
	return (0);
}
