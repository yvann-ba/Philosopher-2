#include "philo.h"

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

t_philo *init_philos(t_params *params, pthread_mutex_t *forks, pthread_mutex_t *write_mutex)
{
	t_philo	*philo;
	int		i;

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
