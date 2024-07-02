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
	return (0);
}

static int	init_resources(t_params *params, pthread_mutex_t **forks,
	pthread_mutex_t **write_mutex)
{
	*forks = malloc(sizeof(pthread_mutex_t) * params->num_philos);
	*write_mutex = init_write_mutex();
	if (!(*forks) || !(*write_mutex))
	{
		printf("Error: Failed to initialize forks or write mutex\n");
		free(*forks);
		free(*write_mutex);
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
		cleanup(*philo, forks, write_mutex, params->num_philos);
		return (1);
	}
	start_simulation(*philo, params->num_philos);
	return (0);
}

static void	wait_for_philosophers(t_philo *philo, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_join(philo[i].thread, NULL);
		if (num_philos > 1)
			pthread_join(philo[i].monitor_thread, NULL);
		i++;
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
	t_params		params;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*write_mutex;

	if (init_params(&params, argc, argv))
		return (1);
	if (init_resources(&params, &forks, &write_mutex))
		return (1);
	if (launch_philosophers(&philo, &params, forks, write_mutex))
		return (1);
	wait_for_philosophers(philo, params.num_philos);
	cleanup(philo, forks, write_mutex, params.num_philos);
	return (0);
}
