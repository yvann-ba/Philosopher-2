#include "philo.h"

int	init_params(t_params *params, int argc, char **argv)
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
	params->is_dead = 0;
	pthread_mutex_init(&params->is_dead_mutex, NULL);
	pthread_mutex_init(&params->all_eaten_mutex, NULL);
	pthread_mutex_init(&params->write_mutex, NULL);
	return (0);
}

int	init_forks(t_params *params)
{
	int	i;
	
	params->forks = malloc(sizeof(pthread_mutex_t) * params->num_philos);
	if (!(params->forks))
	{
		printf("Error: Failed to initialize forks\n");
		free(params->forks);
		return (1);
	}
	i = 0;
	while (i < params->num_philos)
	{
	    pthread_mutex_init(&(params->forks)[i], NULL);
		i++;
	}
	return (0);
}

t_philo *init_philos(t_params *params)
{
	int	i;

	params->philo = malloc(sizeof(t_philo) * params->num_philos);
	if (!params->philo)
	{
		printf("Error: Failed to initialize philosophers\n");
		return (NULL);
	}	
	i = 0;
	while (i < params->num_philos)
	{
		params->philo[i].id = i + 1;
		printf("philo id: %d\n", params->philo[i].id);
		params->philo->num_meals = 0;
		pthread_mutex_init(&params->philo->meal_mutex, NULL);
		params->philo->last_meal = 0;
		params->philo->params = params;
		params->start_time = get_current_time_in_ms();
		i++;
	}
	return (params->philo);
}
