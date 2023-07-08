/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:50:16 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/07/09 00:41:13 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

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

long long	current_time()
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * (long long)1000) + (t.tv_usec / 1000));
}

/*void	print_log(char *str, t_philo *philo)
{
    long long t;

    pthread_mutex_lock(&philo->data->write);
    t = current_time() - philo->data->start_time;

	pthread_mutex_lock(&philo->data->lock);
	int dead_flag = philo->data->dead;  // Read the value atomically

    if (ft_strcmp("died", str) == 0 && dead_flag == 0)
	{
		printf("%lldms: Philo %d %s\n", t, philo->id, str);
		philo->data->dead = 1;
	}
	pthread_mutex_unlock(&philo->data->lock);
	
    if (!philo->data->dead)
        printf("%lldms: Philo %d %s\n", t, philo->id, str);
    pthread_mutex_unlock(&philo->data->write);
}*/

void	print_log(char *str, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->data->write);
	time = current_time() - philo->data->start_time;
	if (ft_strcmp("died", str) == 0 && philo->data->dead == 0)
	{
		printf("%llu %d %s\n", time, philo->id, str);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%llu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}