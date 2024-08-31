/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:19:01 by ybarbot           #+#    #+#             */
/*   Updated: 2024/08/30 13:38:14 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	int	right_fork;
	int	left_fork;

	if (!philo->params || !philo)
		return ;
	right_fork = 0;
	left_fork = 0;
	right_fork = (philo->id) % philo->params->num_philos;
	left_fork = philo->id - 1;
	pthread_mutex_lock(&philo->params->forks[left_fork]);
	safe_write(philo, " has taken a fork\n");
	pthread_mutex_lock(&philo->params->forks[right_fork]);
	safe_write(philo, " has taken a fork\n");
}

void	eat(t_philo *philo)
{
	if (!philo->params || !philo)
		return ;
	safe_write(philo, " is eating\n");
	pthread_mutex_lock(&philo->params->meal_mutex);
	philo->last_meal = get_current_time_in_ms();
	philo->num_meals++;
	pthread_mutex_unlock(&philo->params->meal_mutex);
	ft_usleep(philo->params->time_to_eat);
	pthread_mutex_unlock(&philo->params->forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->params->forks[(philo->id) \
	% philo->params->num_philos]);
}

void	sleep_and_think(t_philo *philo)
{
	if (!philo->params || !philo)
		return ;
	safe_write(philo, " is sleeping\n");
	ft_usleep(philo->params->time_to_sleep);
	safe_write(philo, " is thinking\n");
}
