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

unsigned long get_time_in_ms(struct timeval start)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return ((now.tv_sec - start.tv_sec) * 1000 + (now.tv_usec - start.tv_usec) / 1000);
}
//protect dead mutex search quand queuqeun es tmort
void cleanup(t_philo *philo, pthread_mutex_t *forks, pthread_mutex_t *write_mutex, int num_philos)
{
    int i;

	i = 0;
    while (i < num_philos)
    {
        pthread_mutex_destroy(&forks[i]);
        pthread_mutex_destroy(&philo[i].meal_mutex);
		i++;
    }
    if (write_mutex)
        pthread_mutex_destroy(write_mutex);
    free(forks);
    free(write_mutex);
    free(philo);
}
