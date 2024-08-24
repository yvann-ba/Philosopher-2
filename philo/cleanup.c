#include "philo.h"

int	error_handle(const char *msg, t_params *params)
{
	if (params)
	{
		if (params->philo)
			join_philos(params);
		// if (params->forks)
		// 	free_forks(params);
	}
	printf("Error: %s\n", msg);
	return (0);
}

void cleanup(t_params *params)
{
    int i;

	i = 0;
    // while (i < params->num_philos)
    // {
    //     pthread_mutex_destroy(params&forks[i]);
    //     pthread_mutex_destroy(&philo[i].meal_mutex);
	// 	i++;
    // }
    // pthread_mutex_destroy(&params->write_mutex);
    // pthread_mutex_destroy(&params->all_eaten_mutex);
    // pthread_mutex_destroy(&params->is_dead_mutex);
    free(params->forks);
    free(params->philo);
}

int clean_exit(t_params *params)
{
    join_philos(params);
    cleanup(params);
    return (0);
}