/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:27:09 by bhung-yi          #+#    #+#             */
/*   Updated: 2023/07/10 19:31:31 by bhung-yi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int just_one_philo(t_data *data)
{
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return 0;
	data->start_time = get_time();
	philo_print(data, 0, "has taken a fork");
	philo_wait(data->time_to_die);
	philo_print(data, 0, "died");
	philo_free(data);
	return 1;
}

int main(int ac, char **argv)
{
	t_data data;

	if (!init_input(ac, argv, &data))
		return 0;
	if (!init_p_f(&data))
		return 0;
	if (data.nb_of_philo == 1)
	{
		return just_one_philo(&data);
	}
	if (!init_threads(&data))
		return (0);
	return (destroy_and_free(&data));
}
