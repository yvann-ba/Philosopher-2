/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:51:11 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/20 11:49:31 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//args: 
//number_of_philosophers 
//time_to_die 
//time_to_eat 
//time_to_sleep
//[number_of_times_each_philosopher_must_eat]
int main(int argc, char **argv)
{
	if (check_args(argc, argv))
	{
		return (1);
	}
	return (0);
}