#include "philo.h"

void *monitor_routine(void *arg)
{
    t_philo *philo;
	unsigned long current_time;
	unsigned long last_meal_time;
    int meals;
	
	philo = (t_philo *)arg;
    while (1)
    {
        usleep(1000);
        current_time = get_time_in_ms(philo->start_time);
        pthread_mutex_lock(&philo->meal_mutex);
		last_meal_time = get_time_in_ms(philo->last_meal);
        meals = philo->num_meals;
        pthread_mutex_unlock(&philo->meal_mutex);
        if (current_time - last_meal_time > (unsigned long)philo->time_to_die * 1000)
        {
            safe_write(philo, " died\n");
            exit(0);
        }
        if (philo->max_meals != -1 && meals >= philo->max_meals)
        {
            return (NULL);
        }
    }
    return (NULL);
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
    i = 0;
    while (i < num_philos)
    {
        if (pthread_join(philo[i].thread, NULL) != 0)
        {
            safe_write(philo, " Error: Failed to join thread\n");
            return;
        }
        i++;
    }
}
