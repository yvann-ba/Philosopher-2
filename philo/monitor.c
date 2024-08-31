/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:03:07 by ybarbot           #+#    #+#             */
/*   Updated: 2024/08/30 13:36:07 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_died(t_philo *philo)
{
	long long	current_time;

	pthread_mutex_lock(&philo->params->is_dead_mutex);
	if (philo->params->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->params->is_dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->params->is_dead_mutex);
	pthread_mutex_lock(&philo->params->meal_mutex);
	current_time = get_current_time_in_ms();
	if (philo->params->num_philos != 1 && \
	(current_time - philo->last_meal > philo->params->time_to_die))
	{
		safe_write(philo, " died\n");
		pthread_mutex_lock(&philo->params->is_dead_mutex);
		philo->params->is_dead = 1;
		pthread_mutex_unlock(&philo->params->is_dead_mutex);
		pthread_mutex_unlock(&philo->params->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->params->meal_mutex);
	return (0);
}

int	check_all_eaten(t_params *params)
{
	if (params->max_meals != -1)
	{
		pthread_mutex_lock(&params->all_eaten_mutex);
		//printf("-------------------all_eaten: %d\n", params->all_eaten);
		if (params->all_eaten == params->num_philos)
		{
		//	safe_write(&params->philo[0], "-----------------------------------All meals eaten\n"); 	
			pthread_mutex_unlock(&params->all_eaten_mutex);
			return (1);
		}
		pthread_mutex_unlock(&params->all_eaten_mutex);
	}
	return (0);
}

int	monitor_philo(t_params *params)
{
	int	i;

	while (1)
	{
		if (check_all_eaten(params))
			return (1);
		pthread_mutex_lock(&params->is_dead_mutex);
		if (params->is_dead == 1)
		{
			pthread_mutex_unlock(&params->is_dead_mutex);
			return (1);
		}
		pthread_mutex_unlock(&params->is_dead_mutex);
		i = 0;
		while (i < params->num_philos)
		{
			if (is_philo_died(&params->philo[i++]))
				break ;
		}
		usleep(10000);
	}
	return (0);
}
