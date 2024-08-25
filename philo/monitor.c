#include "philo.h"

int is_philo_died(t_philo *philo)
{
	long long current_time;

	pthread_mutex_lock(&philo->params->is_dead_mutex);
	if (philo->params->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->params->is_dead_mutex);
		return (1);
	}
    pthread_mutex_lock(&philo->params->meal_mutex);
    current_time = get_current_time_in_ms();

	if (philo->params->num_philos != 1 && (current_time - philo->last_meal > philo->params->time_to_die))
	{
		safe_write(philo, " is died\n");

		philo->params->is_dead = 1;
		pthread_mutex_unlock(&philo->params->is_dead_mutex);
        pthread_mutex_unlock(&philo->params->meal_mutex);
		return (1);
	}
    pthread_mutex_unlock(&philo->params->meal_mutex);
	pthread_mutex_unlock(&philo->params->is_dead_mutex);

	return (0);
}
int monitor_philo(t_params *params)
{
	int i;

	while (1)
	{
		i = 0;
        if (params->max_meals != -1)
        {
            pthread_mutex_lock(&params->all_eaten_mutex);
            if (params->all_eaten == params->num_philos)
            {
                pthread_mutex_unlock(&params->all_eaten_mutex);
                printf("All philos ate %d times\n", params->max_meals);
                return (1);
            }
            pthread_mutex_unlock(&params->all_eaten_mutex);
        }

		pthread_mutex_lock(&params->is_dead_mutex);
		if (params->is_dead == 1)
		{
            pthread_mutex_unlock(&params->is_dead_mutex);
			clean_exit(params);
			return (1);
		}
        pthread_mutex_unlock(&params->is_dead_mutex);
		while (i < params->num_philos)
        {
			if (is_philo_died(&params->philo[i++]))
				break;
        }
		usleep(10000);
	}
    return (0);
}