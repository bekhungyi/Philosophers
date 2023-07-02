/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:27:42 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/07/03 00:57:41 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*check_meal(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->finish_meal >= philo->data->nb_of_philo)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*check_dead(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (current_time() >= philo->lifetime && philo->eating == 0)
			print_log("is dead", philo);
		if (philo->eat_count == philo->data->nb_of_meal)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finish_meal++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	philo->lifetime = current_time() + philo->data->time_to_die;
	if (pthread_create(&philo->dead_t, NULL, &check_dead, (void *)philo))
		return ((void *)1);
	while (philo->data->dead == 0)
	{
		eating(philo);
		print_log("is thinking.", philo);
	}
	if (pthread_join(philo->dead_t, NULL))
		return ((void *)1);
	return ((void *)0);
}

int	thread_init(t_data *data)
{
	int			i;
    pthread_t   meal_t;

	if (data->nb_of_meal > 0)
	{
		if (pthread_create(&meal_t, NULL, &check_meal, &data->philo[0]))
			return (1);
	}
	i = 0;
    while (i < data->nb_of_philo)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philo[i]) != 0)
			return (1);
		i++;
		usleep(1);
	}
	i = 0;
	while (i < data->nb_of_philo)
	{
		if (pthread_join(data->tid[i], NULL))
			return (1);
		i++;
	}
    return (0);
}