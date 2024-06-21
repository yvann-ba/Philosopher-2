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
            printf("Philosopher %d died\n", philo->id);
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
		printf("Philosopher %d is thinking\n", philo->id);
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
		printf("Philosopher %d is eating\n", philo->id);
		gettimeofday(&philo->last_meal, NULL);
		usleep(philo->time_to_eat * 1000);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
		philo->num_meals++;
		if (philo->max_meals != -1 && philo->num_meals >= philo->max_meals)
			break;
		printf("Philosopher %d is sleeping\n", philo->id);
		usleep(philo->time_to_sleep * 1000);
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
            printf("Error: Failed to create thread for philosopher %d\n", philo[i].id);
            return ;
        }
		i++;
    }
    i = 0;
    while (i < num_philos)
    {
        if (pthread_join(philo[i].thread, NULL) != 0)
        {
            printf("Error: Failed to join thread for philosopher %d\n", philo[i].id);
            return;
        }
        i++;
    }
}
