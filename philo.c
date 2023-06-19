/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:27:09 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/06/18 16:36:32 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	num = 0;
pthread_mutex_t	mutex;

void	*function()
{
	for (int i = 0; i < 10; i++)
	{
		pthread_mutex_lock(&mutex);
		num++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;
	time_t		t;
	
	t = time(NULL);
	av_init(ac, av, &data);
	eating(1, &data);
	thinking(1, &data);
	sleeping(1, &data);
	thinking(1, &data);

	return (0);
}
