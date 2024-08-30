/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 09:59:04 by ybarbot           #+#    #+#             */
/*   Updated: 2024/08/30 10:43:23 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_handle(const char *msg, t_params *params)
{
	if (params)
	{
		if (params->philo)
			join_philos(params);
		if (params->forks)
			free_forks(params);
		free_params(params);
	}
	printf("Error: %s\n", msg);
	return (0);
}

void	join_philos(t_params *params)
{
	int	i;

	i = 0;
	while (i < params->num_philos)
	{
		pthread_join(params->philo[i].thread, NULL);
		i++;
	}
}

void	free_params(t_params *params)
{
	if (params)
	{
		if (params->philo)
		{
			free(params->philo);
			params->philo = NULL;
		}
		free(params);
		params = NULL;
	}
}

void	free_forks(t_params *params)
{
	int	i;

	if (params && params->forks)
	{
		i = 0;
		while (i < params->num_philos)
		{
			pthread_mutex_destroy(&params->forks[i]);
			i++;
		}
		free(params->forks);
		params->forks = NULL;
	}
}

int	clean_exit(t_params *params)
{
	if (params)
	{
		join_philos(params);
		free_forks(params);
		free_params(params);
	}
	return (0);
}
