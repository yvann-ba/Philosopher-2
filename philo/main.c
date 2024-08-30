/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:39:01 by ybarbot           #+#    #+#             */
/*   Updated: 2024/08/30 10:39:29 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_params	*params;

	params = malloc(sizeof(t_params));
	if (init_params(params, argc, argv) || init_forks(params) \
	|| init_philos(params) == NULL)
		return (1);
	start_simulation(params, params->num_philos);
	monitor_philo(params);
	clean_exit(params);
	return (0);
}
