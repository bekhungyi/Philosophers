/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:27:57 by jchu              #+#    #+#             */
/*   Updated: 2023/07/10 19:49:41 by bhung-yi         ###   ########.fr       */
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
	if (n < 0 || ((str[i] < '0' || str[i] > '9') && str[i] != '\0')
		|| n > 2147483647)
		return (0);
	return (n);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
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

int	philo_print(t_vault *vault, int id, char *action)
{
	long long	now;

	now = delta_time(vault->time);
	if (vault->dead == 1)
		return (0);
	pthread_mutex_unlock(&vault->output);
	if (vault->dead == 1)
	{
		pthread_mutex_unlock(&vault->output);
		return (0);
	}
	else
		printf("%lld %d %s\n", now, id + 1, action);
	pthread_mutex_unlock(&vault->output);
	return (1);
}
