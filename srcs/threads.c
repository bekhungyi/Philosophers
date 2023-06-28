/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:27:42 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/06/28 20:37:18 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*checker(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	pthread_mutex_lock(&philo->data->write);
	printf("data val: %d", philo->data->dead);
	pthread_mutex_unlock(&philo->data->write);
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->done_eating >= philo->data->nb_of_philo)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void *routine(void *philo_ptr) {
    t_philo *philo = (t_philo *)philo_ptr;

    while (philo->data->dead == 0) {
        int id = philo->id;  // Get the philosopher ID
        printf("Philosopher %d is alive.\n", id);  // Print the philosopher ID
        eating(id, philo->data);  // Pass the philosopher ID to the eating function
        thinking(id, philo->data);  // Pass the philosopher ID to the thinking function
    }

    int id = philo->id;  // Get the philosopher ID
    printf("Philosopher %d has died.\n", id);  // Print the philosopher ID
    if (pthread_join(philo->data->tid[0], NULL) != 0) {
        return (void *)1;
    }
    return (void *)0;
}

int	thread_init(t_data *data)
{
	int	i;
    pthread_t   t;

	i = 0;
	if (data->nb_of_meal > 0)
	{
		if (pthread_create(&t, NULL, &checker, &data->philo[0]))
			return (0);
	}
    while (++i < data->nb_of_philo)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philo[i]))
        {
            printf("Error creating thread for philosopher %d.\n", i);
			return (0);
        }
		usleep(1);
	}
    printf("All philosopher threads created successfully.\n");
    return (1);
}