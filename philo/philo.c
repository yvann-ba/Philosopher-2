#include "philo.h"

void start_simulation(t_params *params, int num_philos)
{
    int i;

    i = 0;
    while (i < num_philos)
    {
        if (pthread_create(params->philo[i].thread, NULL, philo_routine, &params->philo[i]) != 0)
        {
            safe_write(&params->philo[i], " Error: Failed to create thread\n");
            return ;
        }
    }
}
