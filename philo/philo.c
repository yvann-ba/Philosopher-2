/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:09:33 by ybarbot           #+#    #+#             */
/*   Updated: 2024/08/30 10:34:31 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_simulation(t_params *params, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_create(&params->philo[i].thread, NULL, \
		philo_routine, &params->philo[i]) != 0)
		{
			safe_write(&params->philo[i], " Error: Failed to create thread\n");
			return ;
		}
		i++;
	}
}
