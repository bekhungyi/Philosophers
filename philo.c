/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:27:09 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/06/28 19:19:19 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

// void	ft_exit(t_data *data)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < data->philo_num)
// 	{
// 		pthread_mutex_destroy(&data->fork[i]);
// 		pthread_mutex_destroy(&data->philos[i].lock);
// 	}
// 	pthread_mutex_destroy(&data->write);
// 	pthread_mutex_destroy(&data->lock);
// 	clear_data(data);
// }

int	one_philo(t_data *data)
{
	take_fork(1, data);
	usleep(data->time_to_die * 1000);
	die(1, data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	time_t		t;
	
	if (ac != 5 && ac != 6)
    {
        printf("\033[31mError: Invalid number of arguments.\033[0m\n");
        exit(1);
    }
	t = time(NULL);
	if (!data_init(ac, av, &data))
		return (0);
	if (data.nb_of_philo == 1)
		return(one_philo(&data));
	if (thread_init(&data))
		return (1);
	// return(ft_exit(&data));
	return (0);
}
