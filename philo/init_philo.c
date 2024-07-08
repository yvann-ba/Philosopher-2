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
	pthread_mutex_init(&params->all_eaten_mutex, NULL);
	pthread_mutex_init(&params->is_dead_mutex, NULL);
	pthread_mutex_init(&params->write_mutex, NULL);
	params->start_time = get_current_time_in_ms();

	return (0);
}

int	init_resources(t_params *params, pthread_mutex_t **forks)
{
	int	i;
	
	*forks = malloc(sizeof(pthread_mutex_t) * params->num_philos);
	if (!(*forks))
	{
		printf("Error: Failed to initialize forks\n");
		// free(*forks);
		return (1);
	}
	i = 0;
	while (i < params->num_philos)
	{
	    pthread_mutex_init(&(*forks)[i], NULL);
		i++;
	}
	return (0);
}

void init_philo_data(t_philo *philo, int id, t_params *params, pthread_mutex_t *forks)
{
	philo->id = id;
	philo->num_meals = 0;
	philo->left_fork = &forks[id - 1];
	pthread_mutex_init(&philo->meal_mutex, NULL);
	philo->right_fork = &forks[id % params->num_philos];
	philo->last_meal = 0;
	philo->params = params;
}

t_philo *init_philos(t_params *params, pthread_mutex_t *forks)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * params->num_philos);
	if (!philo || !forks)
		return (NULL);
	i = 0;
	while (i < params->num_philos)
	{
		init_philo_data(&philo[i], i + 1, params, forks);
		i++;
	}
	return (philo);
}
