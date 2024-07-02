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
        current_time = get_time_in_ms(philo->start_time);
		last_meal_time = get_time_in_ms(philo->last_meal);
		        //printf("Philo %d: current_time = %lu, last_meal_time = %lu, time_to_die = %d\n",
               //philo->id, current_time, last_meal_time, philo->time_to_die);
        if (current_time - last_meal_time > (unsigned long)philo->time_to_die * 1000)
        {
            safe_write(philo, " died\n");
			//cleanup(philo, philo->left_fork, philo->write_mutex, philo->num_philos);
            exit(0);
        }
    }
    return (NULL);
}

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->num_philos > 1)
    pthread_create(&philo->monitor_thread, NULL, monitor_routine, philo);
    else
    {
        pthread_mutex_lock(philo->left_fork);
        safe_write(philo, " has taken the left fork\n");
        usleep(philo->time_to_die * 1000);
        safe_write(philo, " has died\n");
        pthread_mutex_unlock(philo->left_fork);
        return NULL;
    }
    while (1)
    {
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(philo->left_fork);
            safe_write(philo, " has taken the left fork\n");
            pthread_mutex_lock(philo->right_fork);
            safe_write(philo, " has taken the right fork\n");
        }
        else
        {
			usleep(100);
            pthread_mutex_lock(philo->right_fork);
            safe_write(philo, " has taken the right fork\n");
            pthread_mutex_lock(philo->left_fork);
            safe_write(philo, " has taken the left fork\n");
        }
		gettimeofday(&philo->last_meal, NULL);
        safe_write(philo, " is eating\n");
        usleep(philo->time_to_eat * 1000);

        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        safe_write(philo, " has put down the forks\n");

        philo->num_meals++;
        if (philo->max_meals != -1 && philo->num_meals >= philo->max_meals)
            break;

        safe_write(philo, " is sleeping\n");
        usleep(philo->time_to_sleep * 1000);
        safe_write(philo, " is thinking\n");
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
