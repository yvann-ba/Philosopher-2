#include "philo.h"

void *monitor_routine(void *arg)
{
    t_philo *philo;
	unsigned long current_time;
	unsigned long last_meal_time;
	
	philo = (t_philo *)arg;
    while (1)
    {
        usleep(1000);
        current_time = get_time_in_ms();
        last_meal_time = (philo->last_meal.tv_sec * 1000) + (philo->last_meal.tv_usec / 1000);

        if (current_time - last_meal_time > (unsigned long)philo->time_to_die)
        {
            safe_write(philo->id, " died, current time=");
            ft_putnbr(current_time);
            ft_putstr("\n");
            exit(0);
        }
    }
    return (NULL);
}

void *philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	pthread_create(&philo->monitor_thread, NULL, monitor_routine, philo);
	while (1)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(philo->left_fork);
		}
		safe_write(philo->id, " is eating\n");
		gettimeofday(&philo->last_meal, NULL);
		usleep(philo->time_to_eat * 1000);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
		philo->num_meals++;
		if (philo->max_meals != -1 && philo->num_meals >= philo->max_meals)
			break;
		safe_write(philo->id, " is sleeping\n");
		usleep(philo->time_to_sleep * 1000);
		safe_write(philo->id, " is thinking\n");
		usleep(100);
	}
	return (NULL);
}

void start_simulation(t_philo *philo, int num_philos)
{
    int i;

    i = 0;
    while (i < num_philos)
    {
        if (pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]) != 0)
        {
            safe_write(philo[i].id, " Error: Failed to create thread\n");
            return ;
        }
		i++;
    }
    i = 0;
    while (i < num_philos)
    {
        if (pthread_join(philo[i].thread, NULL) != 0)
        {
            safe_write(philo[i].id, " Error: Failed to join thread\n");
            return;
        }
        i++;
    }
}
