/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:50:16 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/08/31 21:52:37 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
		|| n > INT_MAX)
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
	struct timeval	start_time;
	struct timeval	current_time;
	long			elapsed_time;

	gettimeofday(&start_time, NULL);
	while (1)
	{
		gettimeofday(&current_time, NULL);
		elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000000
			+ (current_time.tv_usec - start_time.tv_usec);
		if (elapsed_time >= (time * 1000))
			break ;
		usleep(50);
	}
}

int	philo_print(t_vault *vault, int id, char *action)
{
	if (check_dead(vault))
		return (0);
	pthread_mutex_lock(&(vault->output));
	if (check_dead(vault))
	{
		pthread_mutex_unlock(&(vault->output));
		return (0);
	}
	else
		printf("%lld %d %s\n", delta_time(vault->time), id + 1, action);
	pthread_mutex_unlock(&(vault->output));
	return (1);
}
