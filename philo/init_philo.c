#include "philo.h"

void init_philo_data(t_philo *philo, int id, t_params *params, pthread_mutex_t *forks)
{
	philo->id = id;
	philo->time_to_die = params->time_to_die;
	philo->time_to_eat = params->time_to_eat;
	philo->time_to_sleep = params->time_to_sleep;
	philo->num_meals = 0;
	philo->max_meals = params->max_meals;
	philo->left_fork = &forks[id - 1];
	philo->right_fork = &forks[id % params->num_philos];
	gettimeofday(&philo->last_meal, NULL);
}

t_philo *init_philos(t_params *params, pthread_mutex_t *forks)
{
	t_philo *philo;
	int i;

	philo = malloc(sizeof(t_philo) * params->num_philos);
	if (!philo || !forks)
		return (NULL);
	i = 0;
	while (i < params->num_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		init_philo_data(&philo[i], i + 1, params, forks);
		i++;
	}
	return (philo);
}