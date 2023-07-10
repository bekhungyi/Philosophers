/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:27:42 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/07/10 19:33:44 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void *process(void *args)
{
	int i;
	t_data *data;

	data = (t_data *)args;
	i = data->tid;
	if (data->nb_of_meal > 0)
	{
		while (data->nb_of_meal > data->philo[i].eat_count && data->dead == 0)
			routine_execute(data, i);
	}
	else
	{
		while (data->dead == 0)
		{
			if (routine_execute(data, i) == 0)
				break;
		}
	}
	return (0);
}

int routine_execute(t_data *data, int i)
{
	if (eating(data, i) == 0)
		return (0);
	if (data->nb_of_meal != data->philo[i].eat_count)
	{
		if (sleeping(data, i) == 0)
			return (0);
		if (thinking(data, i) == 0)
			return (0);
	}
	return (1);
}

int philo_is_dead(t_data *data, int *i)
{
	int time;

	if (*i == data->nb_of_philo)
		*i = 0;
	time = delta_time(data->philo[*i].lifetime);
	if (time > data->time_to_die)
	{
		philo_print(data, data->philo[*i].id, "died");
		data->dead = 1;
		return (1);
	}
	i++;
	return (0);
}

void *threads_checker(void *args)
{
	int i;
	t_data *data;

	i = 0;
	data = (t_data *)args;
	if (data->nb_of_meal > 0)
	{
		while (data->nb_of_meal > data->philo[i].eat_count && data->dead == 0)
		{
			if (philo_is_dead(data, &i) == 1)
				break;
		}
	}
	else
	{
		while (data->dead == 0)
		{
			if (philo_is_dead(data, &i) == 1)
				break;
		}
	}
	return (0);
}

int init_threads(t_data *data)
{
	int i;

	i = 0;
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return 0;
	while (i < data->nb_of_philo)
	{
		data->tid = i;
		if (pthread_create(&data->philo[i].thread, NULL, &process, (void*)data) != 0)
			return 0;
		i++;
		philo_wait(1);
	}
	if (pthread_create(&data->dead_t, NULL, &threads_checker, (void*)data) != 0)
		return 0;
	philo_wait(1);
	return (join_threads(data));
}

int join_threads(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_join(data->dead_t, NULL) != 0)
		return (0);
	return 1;
}

void philo_free(t_data *data)
{
	free(data->philo);
	free(data->fork);
}

int destroy_and_free(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_of_fork)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	philo_free(data);
	return (1);
}