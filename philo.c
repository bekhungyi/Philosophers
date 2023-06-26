/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:27:09 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/06/25 17:50:56 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	one_philo(t_data *data)
{
	take_fork(1, data);
	usleep(data->time_to_die * 1000);
	die(1, data);
	return (1);
}

int	main(int ac, char **av)
{
	t_data		data;
	time_t		t;
	
	if (ac != 5 && ac != 6)
    {
        printf("Error: Invalid number of arguments.\n");
        exit(1);
    }
	t = time(NULL);
	if (!av_init(ac, av, &data))
		return (0);
	if (data.number_of_philosophers == 1)
	{
		one_philo(&data);
		return (0);
	}

	return (0);
}
