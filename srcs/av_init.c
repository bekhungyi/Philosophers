/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   av_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:53:21 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/06/18 16:06:12 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    av_init(int ac, char **av, t_data *data)
{
    if (ac != 5)
    {
        printf("Error: Invalid number of arguments\n");
        exit(1);
    }
    data->number_of_philosophers = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
	data->start_time = current_time();
}