/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:50:16 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/07/10 19:41:21 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(char *str)
{
	int			i;
	long int	n;

	i = 0;
	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	if (n < 0 || ((str[i] < '0' || str[i] > '9') && str[i] != '\0') || n > INT_MAX)
		return (0);
	return (n);
}

long long	get_time()
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * (long long)1000) + (t.tv_usec / 1000));
}

long long	delta_time(long long time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}

void	philo_wait(long long time)
{
	usleep(time * 1000);
}

int	philo_print(t_data *data, int id, char *str)
{
	long long	t;

	t = delta_time(data->start_time);
	if (data->dead == 1)
		return (0);
	pthread_mutex_unlock(&data->write);
	if (data->dead == 1)
	{
		pthread_mutex_unlock(&data->write);
		return (0);
	}
	else
		printf("%lld %d %s\n", t, id + 1, str);
	pthread_mutex_unlock(&data->write);
	return (1);
}