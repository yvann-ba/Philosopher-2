#include "philo.h"

// int check_end(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->params->simulation_mutex);
// 	if (!philo->params->simulation_running)
// 	{
// 		pthread_mutex_unlock(&philo->params->simulation_mutex);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->params->simulation_mutex);
// 	return (0);
// }

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		// if (check_end(philo))
		// 	return ;
		pthread_mutex_lock(philo->left_fork);
		safe_write(philo, " has taken the left fork\n");
		pthread_mutex_lock(philo->right_fork);
		safe_write(philo, " has taken the right fork\n");
	}
	else
	{
		// if (check_end(philo))
		// 	return ;
		pthread_mutex_lock(philo->right_fork);
		safe_write(philo, " has taken the right fork\n");
		pthread_mutex_lock(philo->left_fork);
		safe_write(philo, " has taken the left fork\n");
	}
}

static void eat(t_philo *philo)
{
	// if (check_end(philo))
	// 	return ;
    pthread_mutex_lock(&philo->meal_mutex);
    gettimeofday(&philo->last_meal, NULL);
    philo->num_meals++;
    pthread_mutex_unlock(&philo->meal_mutex);
    safe_write(philo, " is eating\n");
	pthread_mutex_lock(philo->write_mutex);
    usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->write_mutex);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    safe_write(philo, " has put down the forks\n");
}

static void	sleep_and_think(t_philo *philo)
{
	// if (check_end(philo))
	// 	return ;
	safe_write(philo, " is sleeping\n");
	pthread_mutex_lock(philo->write_mutex);
	usleep(philo->time_to_sleep * 1000);
	pthread_mutex_unlock(philo->write_mutex);
	safe_write(philo, " is thinking\n");
}


void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    monitor_thread(philo);
    while (1)
    {
        pthread_mutex_lock(&philo->params->simulation_mutex);
        if (!philo->params->simulation_running)
        {
            pthread_mutex_unlock(&philo->params->simulation_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->params->simulation_mutex);

        take_forks(philo);
		// if (check_end(philo))
		// 	return (NULL);
        eat(philo);
		// if (check_end(philo))
		// 	return (NULL);
        sleep_and_think(philo);
		// if (check_end(philo))
		// 	return (NULL);
    }
    return NULL;
}