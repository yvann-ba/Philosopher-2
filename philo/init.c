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
	pthread_mutex_init(&params->meal_mutex, NULL);
	if (pthread_mutex_init(&params->is_dead_mutex, NULL) || \
	pthread_mutex_init(&params->all_eaten_mutex, NULL) || \
	pthread_mutex_init(&params->write_mutex, NULL) != 0)
	{
		printf("Error: Failed to initialize mutex\n");
		return (1);
	}
	return (0);
}

int	init_forks(t_params *params)
{
	int	i;
	
	params->forks = malloc(sizeof(pthread_mutex_t) * params->num_philos);
	if (!(params->forks))
	{
		printf("Error: Failed to allocate memory for forks\n");
		return (1);
	}
	i = 0;
	while (i < params->num_philos)
	{
	    if (pthread_mutex_init(&(params->forks)[i], NULL) != 0)
		{
			printf("Error: Failed to initialize mutex for forks\n");
			while (i > 0)
			{
				pthread_mutex_destroy(&(params->forks)[i]);
				i--;
			}
			free(params->forks);
			return (1);
		}
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
	params->philo->last_meal = 0;
	params->start_time = get_current_time_in_ms();
	params->philo->num_meals = 0;

	while (i < params->num_philos)
	{
		params->philo[i].id = i + 1;
		params->philo[i].num_meals = params->num_philos;
		params->philo[i].last_meal = params->start_time;
		params->philo[i].params = params;

		usleep(10);

		i++;
	}
	return (params->philo);
}
