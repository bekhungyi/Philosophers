/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:50:16 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/06/29 19:19:00 by bhung-yi         ###   ########.fr       */
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
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void print_log(int id, char *str, t_data *data) {
    long long t;

    pthread_mutex_lock(&data->write);
    t = (current_time() - data->start_time);
    if (ft_strcmp(str, "is dead.") == 0 && data->dead == 0) {
        printf("%*lldms: Philo %d %s\n", 6, t, id + 1, str); // Add +1 to the id to print the index
        data->dead = 1;
    }
    if (!data->dead)
        printf("%*lldms: Philo %d %s\n", 6, t, id + 1, str); // Add +1 to the id to print the index
    pthread_mutex_unlock(&data->write);
}