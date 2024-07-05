#include "philo.h"

unsigned long get_time_in_ms()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void start_simulation(t_philo *philo, int num_philos)
{
    int i;

    i = 0;
    while (i < num_philos)
    {
        if (pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]) != 0)
        {
            safe_write(philo, " Error: Failed to create thread\n");
            return ;
        }
		i++;
    }
}
