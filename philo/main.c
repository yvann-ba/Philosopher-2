#include "philo.h"

static int	launch_philosophers(t_philo **philo, t_params *params,
	pthread_mutex_t *forks)
{
	*philo = init_philos(params, forks);
	if (!(*philo))
	{
		printf("Error: Failed to initialize philosophers\n");
		cleanup(*philo, forks, params);
		return (1);
	}
	return (0);
}

static void	wait_for_philosophers(t_philo *philo, int num_philos, t_params *params)
{
	int	i;
	(void)params;
	i = 0;
	while (i < num_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

int monitor_simulation(t_philo *philo)
{
    unsigned long current_time;
    unsigned long time_since_last_meal;

    while (1)
    {
        usleep(1000);
        current_time = get_current_time_in_ms();
        pthread_mutex_lock(&philo->meal_mutex);
        time_since_last_meal = current_time - philo->last_meal;
        pthread_mutex_unlock(&philo->meal_mutex);

		// if (time_since_last_meal == current_time)
		// 	time_since_last_meal = 0;

//        pthread_mutex_lock(&philo->params->write_mutex);
//        printf("current time = %ld\nlast meal = %ld\ntime since last meal = %ld\ntime to die = %ld\n", 
//               current_time, philo->last_meal, time_since_last_meal, (unsigned long)philo->params->time_to_die);
//        pthread_mutex_unlock(&philo->params->write_mutex);

        if (time_since_last_meal >= (unsigned long)philo->params->time_to_die)
        {
            safe_write(philo, " has died\n");
            pthread_mutex_lock(&philo->params->is_dead_mutex);
            philo->params->is_dead = 1;
            pthread_mutex_unlock(&philo->params->is_dead_mutex);
            return (1);
        }
        pthread_mutex_lock(&philo->params->all_eaten_mutex);
        if (philo->params->all_eaten == philo->params->num_philos)
        {
            pthread_mutex_unlock(&philo->params->all_eaten_mutex);
            return (1);
        }
        pthread_mutex_unlock(&philo->params->all_eaten_mutex);
    }
	return (0);
}

// args:
//  1 number_of_philosophers
//  2 time_to_die
//  3 time_to_eat
//  4 time_to_sleep
//  5 [number_of_times_each_philosopher_must_eat]
int	main(int argc, char **argv)
{
	t_params		params;
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (init_params(&params, argc, argv))
		return (1);
	if (init_resources(&params, &forks))
		return (1);
	launch_philosophers(&philo, &params, forks);
	start_simulation(philo, params.num_philos);
	monitor_simulation(philo);
	wait_for_philosophers(philo, params.num_philos, &params);
	cleanup(philo, forks, &params);
	return (0);
}
