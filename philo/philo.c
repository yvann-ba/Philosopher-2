#include "philo.h"

void *monitor_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    unsigned long last_meal_time;
    unsigned long start_time;

    
    while (1)
    {
        usleep(1000);
        pthread_mutex_lock(&philo->meal_mutex);
        last_meal_time = get_time_in_ms(philo->last_meal);
        start_time = get_time_in_ms(philo->start_time);
        if (start_time - last_meal_time > (unsigned long)philo->time_to_die)
        {
            pthread_mutex_unlock(&philo->meal_mutex);
            safe_write(philo, " died\n");
            pthread_mutex_lock(&philo->params->simulation_mutex);
            philo->params->simulation_running = 0;
            pthread_mutex_unlock(&philo->params->simulation_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&philo->meal_mutex);

        pthread_mutex_lock(&philo->params->simulation_mutex);
        if (!philo->params->simulation_running)
        {
            pthread_mutex_unlock(&philo->params->simulation_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&philo->params->simulation_mutex);
    }
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
