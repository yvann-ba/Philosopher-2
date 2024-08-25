#include "philo.h"

int	error_handle(const char *msg, t_params *params)
{
	if (params)
	{
		if (params->philo)
			join_philos(params);
		 if (params->forks)
		 	free_forks(params);
	}
	printf("Error: %s\n", msg);
	return (0);
}

void join_philos(t_params *params)
{
	int i;

	i = 0;
	while (i < params->num_philos)
	{
		pthread_join(params->philo[i].thread, NULL);
		i++;
	}
}

void free_params(t_params *params)
{
    free(params);
    free(params->philo);
}

void free_forks(t_params *params)
{
    int i;

	i = 0;
    while (i < params->num_philos)
    {
        pthread_mutex_destroy(&params->forks[i]);
		i++;
    }
    free(params->forks);

}
int clean_exit(t_params *params)
{
    join_philos(params);
    cleanup(params);
    return (0);
}