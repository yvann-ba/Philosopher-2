#include "philo.h"

unsigned long get_time_in_ms2()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	monitor_thread(t_philo *philo)
{
	if (philo->num_philos > 1)
		pthread_create(&philo->monitor_thread, NULL, monitor_routine, philo);
	else
    {
		pthread_mutex_lock(philo->left_fork);
		safe_write(philo, " has taken the left fork\n");
		usleep(philo->time_to_die * 1000);
		safe_write(philo, " has died\n");
		pthread_mutex_unlock(philo->left_fork);
        return ;
    }
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
