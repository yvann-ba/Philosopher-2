#include "philo.h"
// args:
//  1 number_of_philosophers
//  2 time_to_die
//  3 time_to_eat
//  4 time_to_sleep
//  5 [number_of_times_each_philosopher_must_eat]
int main(int argc, char **argv)
{
	t_params params;
	t_philo *philo;
	pthread_mutex_t *forks;
	pthread_mutex_t *write_mutex;
	int i;
	
	if (check_args(argc, argv))
		return (1);
	params.num_philos = ft_atoi(argv[1]);
	params.time_to_die = ft_atoi(argv[2]);
	params.time_to_eat = ft_atoi(argv[3]);
	params.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params.max_meals = ft_atoi(argv[5]);
	else
		params.max_meals = -1;
	forks = malloc(sizeof(pthread_mutex_t) * params.num_philos);
	write_mutex = init_write_mutex();
	if (!forks || !write_mutex)
	{
		printf("Error: Failed to initialize forks or write mutex\n");
		free(forks);
		free(write_mutex);
		return (1);
	}
	philo = init_philos(&params, forks, write_mutex);
	if (!philo)
	{
		printf("Error: Failed to initialize philosophers\n");
		cleanup(philo, forks, write_mutex, params.num_philos);
		return (1);
	}
	start_simulation(philo, params.num_philos);
	i = 0;
	while (i < params.num_philos)
	{
        pthread_join(philo[i].thread, NULL);
        pthread_join(philo[i].monitor_thread, NULL);
		i++;
	}
    cleanup(philo, forks, write_mutex, params.num_philos);
	return (0);
}
