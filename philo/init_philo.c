#include "philo.h"

pthread_mutex_t *init_write_mutex(void)
{
    pthread_mutex_t *write_mutex;

    write_mutex = malloc(sizeof(pthread_mutex_t));
    if (!write_mutex)
        return (NULL);
    pthread_mutex_init(write_mutex, NULL);
    return (write_mutex);
}

void init_philo_data(t_philo *philo, int id, t_params *params, pthread_mutex_t *forks)
{
	philo->id = id;
	philo->num_philos = params->num_philos;
	philo->time_to_die = params->time_to_die;
	philo->time_to_eat = params->time_to_eat;
	philo->time_to_sleep = params->time_to_sleep;
	philo->num_meals = 0;
	philo->max_meals = params->max_meals;
	gettimeofday(&philo->start_time, NULL);
	philo->left_fork = &forks[id - 1];
	philo->right_fork = &forks[id % params->num_philos];
	gettimeofday(&philo->last_meal, NULL);
}

t_philo *init_philos(t_params *params, pthread_mutex_t *forks, pthread_mutex_t *write_mutex)
{
	t_philo *philo;
	int i;

	philo = malloc(sizeof(t_philo) * params->num_philos);
	if (!philo || !forks || !write_mutex)
		return (NULL);
	i = 0;
	while (i < params->num_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		init_philo_data(&philo[i], i + 1, params, forks);
		philo[i].write_mutex = write_mutex;
		i++;
	}
	return (philo);
}