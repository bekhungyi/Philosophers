/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:27:42 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/06/29 19:26:46 by bhung-yi         ###   ########.fr       */
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
		// if (philo->lifetime >= current_time())
		// 	die(philo->id, philo->data);
		if (current_time() >= philo->lifetime)
			die(philo->id, philo->data);
		if (philo->eat_count == philo->data->nb_of_meal)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finish_meal++;
			philo->eat_count++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

// void *routine(void *philo_ptr)
// {    
// 	t_philo *philo = (t_philo *)philo_ptr;

// 	printf("Dead: %d\n", philo->data->dead);
//     while (philo->data->dead == 0) {
//         int id = philo->id;  // Get the philosopher ID
//         printf("Philosopher %d is alive.\n", id);  // Print the philosopher ID
//         eating(id, philo->data);  // Pass the philosopher ID to the eating function
//         thinking(id, philo->data);  // Pass the philosopher ID to the thinking function
//     }

//     int id = philo->id;  // Get the philosopher ID
//     printf("Philosopher %d has died.\n", id);  // Print the philosopher ID
//     if (pthread_join(philo->data->tid[0], NULL) != 0) {
//         return (void *)1;
//     }
//     return (void *)0;
// }

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	if (pthread_create(&philo->dead_t, NULL, &check_dead, philo_ptr))
		return ((void *)1);
	int id = philo->id;
	while (philo->data->dead == 0)
	{
		eating(philo);
		print_log(id, "is thinking.", philo->data);
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
	i = -1;
    while (++i < data->nb_of_philo)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philo[i]))
        {
            printf("Error creating thread for philosopher %d.\n", i);
			return (1);
        }
		usleep(1);
	}
	i = 0;
	while (i < data->nb_of_philo)
	{
		if (pthread_join(data->tid[i], NULL))
			return (1);
		i++;
	}
    printf("All philosopher threads created successfully.\n");
    return (0);
}