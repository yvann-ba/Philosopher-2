/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:23:26 by ybarbot           #+#    #+#             */
/*   Updated: 2024/08/30 10:34:11 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_current_time_in_ms(void)
{
	struct timeval	tv;
	long long		current_time;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000LL + tv.tv_usec / 1000LL);
	return (current_time);
}

long long	get_elapsed_time(long long start_time)
{
	long long	elapsed_time;

	elapsed_time = get_current_time_in_ms() - start_time;
	return (elapsed_time);
}

void	ft_usleep(long long time)
{
	long long	start;

	start = get_current_time_in_ms();
	while (get_current_time_in_ms() - start < time)
		usleep(30);
}
