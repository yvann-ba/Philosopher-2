#include "philo.h"

static int	init_params(t_params *params, int argc, char **argv)
{
	if (check_args(argc, argv))
		return (1);
	params->num_philos = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->max_meals = ft_atoi(argv[5]);
	else
		params->max_meals = -1;
	params->all_eaten = 0;
	pthread_mutex_init(&params->all_eaten_mutex, NULL);
	params->is_died = 0;
	pthread_mutex_init(&params->is_died_mutex, NULL);
	pthread_mutex_init(&params->write_mutex, NULL);
	gettimeofday(&params->start_time, NULL);

	return (0);
}

static int	init_resources(t_params *params, pthread_mutex_t **forks,
	pthread_mutex_t **write_mutex)
{
	*forks = malloc(sizeof(pthread_mutex_t) * params->num_philos);
	if (!(*forks))
	{
		printf("Error: Failed to initialize forks\n");
		free(*forks);
		return (1);
	}
	return (0);
}

static int	launch_philosophers(t_philo **philo, t_params *params,
	pthread_mutex_t *forks, pthread_mutex_t *write_mutex)
{
	*philo = init_philos(params, forks, write_mutex);
	if (!(*philo))
	{
		printf("Error: Failed to initialize philosophers\n");
		cleanup(*philo, forks, write_mutex, params);
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

void *monitor_routine(t_philo *philo)
{
    unsigned long current_time;
    unsigned long time_since_last_meal;

    while (1)
    {
        usleep(1000);
        pthread_mutex_lock(&philo->meal_mutex);
        current_time = get();
        time_since_last_meal = current_time - philo->last_meal;
		if (time_since_last_meal == current_time)
			time_since_last_meal = 0;

        printf("current time = %ld\nlast meal = %ld\ntime since last meal = %ld\ntime to die = %ld\n", 
               current_time, philo->last_meal, time_since_last_meal, (unsigned long)philo->params->time_to_die);
        if (time_since_last_meal >= (unsigned long)philo->params->time_to_die)
        {
            safe_write(philo, " died moni\n");
            pthread_mutex_lock(&philo->params->is_died_mutex);
            philo->params->is_died = 0;
            pthread_mutex_unlock(&philo->params->is_died_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&philo->meal_mutex);
        pthread_mutex_lock(&philo->params->simulation_mutex);
        if (philo->num_meals >= philo->params->max_meals)
        {
            pthread_mutex_unlock(&philo->params->simulation_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&philo->params->simulation_mutex);
    }
}

// args:
//  1 number_of_philosophers
//  2 time_to_die
//  3 time_to_eat
//  4 time_to_sleep
//  5 [number_of_times_each_philosopher_must_eat]
int	main(int argc, char **argv)
{
	t_params		*params;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*write_mutex;
	int i;

	if (init_params(&params, argc, argv))
		return (1);
	if (init_resources(&params, &forks, &write_mutex))
		return (1);
	launch_philosophers(philo, params, forks, write_mutex);
	start_simulation(philo, params->num_philos);
	monitor
	wait_for_philosophers(philo, params->num_philos, &params);
	cleanup(philo, forks, write_mutex, &params);
	return (0);
}
