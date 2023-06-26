/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:01:31 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/06/25 16:46:51 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	die(int id, t_data *data)
{
	print_log(id, "is dead.", data);
	return (1);
}

int	take_fork(int id, t_data *data)
{
	print_log(id, "has taken a fork.", data);
	return (1);
}


int	eating(int id, t_data *data)
{
	print_log(id, "is eating.", data);
	usleep(data->time_to_eat * 1000);
	return (1);
}

int	thinking(int id, t_data *data)
{
	print_log(id, "is thinking.", data);
	return (1);
}

int	sleeping(int id, t_data *data)
{
	print_log(id, "is sleeping.", data);
	usleep(data->time_to_sleep * 1000);
	return (1);
}