/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:53:21 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/07/10 19:40:28 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int init_philos(t_data *data)
{
	int i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * (data->nb_of_philo + 1));
	if (data->philo == NULL)
		return (0);
	while (i < data->nb_of_philo)
	{
		data->philo[i].id = i;
		data->philo[i].eat_count = 0;
		data->philo[i].lifetime = 0;
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = (i + 1) % data->nb_of_philo;
		i++;
	}
	return 1;
}

int init_p_f(t_data *data)
{
	int i;

	if (!init_philos(data))
		return 0;
	data->start_time = get_time();
	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * (data->nb_of_philo + 1));
	if (data->fork == NULL)
		return 0;
	while (i < data->nb_of_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int check_errors(int ac, t_data *data)
{
	if (!data->nb_of_philo)
		printf("ERROR: There is a mistake in the number of philosophers\n");
	if (!data->time_to_die)
		printf("ERROR: There is a mistake in time to die\n");
	if (!data->time_to_eat)
		printf("ERROR: There is a mistake in time to eat\n");
	if (!data->time_to_sleep)
		printf("ERROR: There is a mistake in time to sleep\n");
	if (ac == 6 && !data->nb_of_meal)
		printf("ERROR: There is a mistake in the number of times each philosopher must eat\n");
	if (!data->nb_of_philo || !data->time_to_die || !data->time_to_eat || !data->time_to_sleep || (ac == 6 && !data->nb_of_meal))
		return 0;
	return 1;
}

int init_input(int ac, char **av, t_data *data)
{
	if (ac > 4 && ac < 7)
	{
		data->dead = 0;
		data->nb_of_philo = ft_atoi(av[1]);
		data->time_to_die = ft_atoi(av[2]);
		data->time_to_eat = ft_atoi(av[3]);
		data->time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			data->nb_of_meal = ft_atoi(av[5]);
		else
			data->nb_of_meal = -1;
		return check_errors(ac, data);
	}
	printf("ERROR: The number of arguments must be 4 or 5\n");
	return 0;
}