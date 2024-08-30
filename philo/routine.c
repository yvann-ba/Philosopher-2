/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:20:27 by ybarbot           #+#    #+#             */
/*   Updated: 2024/08/30 11:45:26 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void	handle_single_philo(t_philo *philo)
{
	if (!philo->params || !philo)
		return ;
	safe_write(philo, " has taken a fork\n");
	ft_usleep(philo->params->time_to_die);
	safe_write(philo, " died\n");
	pthread_mutex_lock(&philo->params->is_dead_mutex);
	philo->params->is_dead = 1;
	pthread_mutex_unlock(&philo->params->is_dead_mutex);
	return ;
}

void	handle_philo_routine(t_philo *philo)
{
	while (1)
	{
		take_forks(philo);
		eat(philo);
		sleep_and_think(philo);
		pthread_mutex_lock(&philo->params->is_dead_mutex);
		if (philo->params->is_dead)
		{
			pthread_mutex_unlock(&philo->params->is_dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->params->is_dead_mutex);
		if (philo->params->max_meals != -1 && philo->num_meals >= philo->params->max_meals)
			break ;
	}
	pthread_mutex_lock(&philo->params->all_eaten_mutex);
	philo->params->all_eaten++;
	pthread_mutex_unlock(&philo->params->all_eaten_mutex);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!philo->params || !philo)
		return (NULL);
	if (philo->params->num_philos == 1)
	{
		handle_single_philo(philo);
		return (NULL);
	}
	else
	{
		if (philo->id % 2 == 0)
			usleep(10000);
		handle_philo_routine(philo);
	}
	return (NULL);
}