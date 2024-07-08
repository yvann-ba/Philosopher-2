#include "philo.h"

int ft_is_digit(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;	

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sign * res);
}

// void cleanup(t_params *params)
// {
//     int i;

// 	i = 0;
//     while (i < params->num_philos)
//     {
//         pthread_mutex_destroy(&forks[i]);
//         pthread_mutex_destroy(&philo[i].meal_mutex);
// 		i++;
//     }
//     pthread_mutex_destroy(&params->write_mutex);
//     pthread_mutex_destroy(&params->all_eaten_mutex);
//     pthread_mutex_destroy(&params->is_dead_mutex);
//     free(forks);
//     free(philo);
// }
