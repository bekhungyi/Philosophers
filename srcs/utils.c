/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:50:16 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/07/02 19:45:25 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (*(char *)s1 - *(char *)s2);
}

int	ft_atoi(char *str)
{
	int			i;
	long long	n;

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
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void print_log(char *str, t_philo *philo)
{
    long long t;

    t = current_time() - philo->data->start_time;
    pthread_mutex_lock(&philo->data->write);
    if (ft_strcmp(str, "is dead.") == 0 && philo->data->dead == 0) {
        printf("%*lldms: Philo %d %s\n", 6, t, philo->id, str);
        philo->data->dead = 1;
    }
    if (!philo->data->dead)
        printf("%*lldms: Philo %d %s\n", 6, t, philo->id, str);
    pthread_mutex_unlock(&philo->data->write);
}