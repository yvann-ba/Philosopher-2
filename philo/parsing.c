/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:09:12 by ybarbot           #+#    #+#             */
/*   Updated: 2024/08/30 10:40:26 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args_digits(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_is_digit(argv[i]))
		{
			printf("Error: argument %d is not a number\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_min_times(int argc, char **argv)
{
	if (ft_atoi(argv[2]) < 60)
	{
		printf("Error: wrong time to die\n");
		return (1);
	}
	if (ft_atoi(argv[3]) < 60)
	{
		printf("Error: wrong time to eat\n");
		return (1);
	}
	if (ft_atoi(argv[4]) < 60)
	{
		printf("Error: wrong time to sleep\n");
		return (1);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 1)
	{
		printf("Error: wrong number of times each philosopher must eat\n");
		return (1);
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (check_args_digits(argc, argv))
		return (1);
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
	{
		printf("Error: wrong number of philosophers\n");
		return (1);
	}
	if (check_min_times(argc, argv))
		return (1);
	return (0);
}
