/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:27:09 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/06/29 19:16:30 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		pthread_mutex_destroy(&data->philo[i].lock);
        i++;
	}
	pthread_mutex_destroy(&data->write);
    free(data->fork);
    free(data->philo);
    free(data->tid);
}

// int	one_philo(t_data *data)
// {
// 	eating(1, data);
// 	usleep(data->time_to_die * 1000);
// 	die(1, data);
//     ft_exit(data);
// 	return (0);
// }

int	main(int ac, char **av)
{
	t_data		data;
	
	if (ac != 5 && ac != 6)
    {
        printf("Invalid number of arguments.");
        return(1);
    }
	if (data_init(ac, av, &data))
        return (1);
    // if (data.nb_of_philo == 1)
    //     return (one_philo(&data));
    if (thread_init(&data))
        return (1);
    return (0);
}
