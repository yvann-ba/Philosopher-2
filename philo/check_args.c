/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:56:26 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/20 11:49:38 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// args:
//  1 number_of_philosophers
//  2 time_to_die
//  3 time_to_eat
//  4 time_to_sleep
//  5 [number_of_times_each_philosopher_must_eat]

int check_args_digits(int argc, char **argv)
{
	int i;
	
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
int check_min_times(int argc, char **argv)
{
	if (atoi(argv[2]) < 60)
	{
		printf("Error: wrong time to die\n");
		return (1);
	}
	if (atoi(argv[3]) < 60)
	{
		printf("Error: wrong time to eat\n");
		return (1);
	}
	if (atoi(argv[4]) < 60)
	{
		printf("Error: wrong time to sleep\n");
		return (1);
	}
	if (argc == 6 && atoi(argv[5]) < 1)
	{
		printf("Error: wrong number of times each philosopher must eat\n");
		return (1);
	}
	return (0);
}

int check_limits(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (check_args_digits(argc, argv))
		return (1);
	if (atoi(argv[1]) < 1 || atoi(argv[1]) > 200)
	{
		printf("Error: wrong number of philosophers\n");
		return (1);
	}
	if (check_min_times(argc, argv))
		return (1);
	return (0);
}
int check_args(int argc, char **argv)
{
	if (check_limits(argc, argv))
		return (1);
	return (0);
}
