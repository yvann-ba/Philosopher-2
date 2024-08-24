#include "philo.h"

static void	take_forks(t_philo *philo)
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
            usleep(1000);
            pthread_mutex_lock(philo->right_fork);
            safe_write(philo, " has taken the right fork\n");
            pthread_mutex_lock(philo->left_fork);
            safe_write(philo, " has taken the left fork\n");
    }
}

static void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_current_time_in_ms();
    philo->num_meals++;
    pthread_mutex_unlock(&philo->meal_mutex);
    safe_write(philo, " is eating\n");
	//pthread_mutex_lock(&philo->params->write_mutex);
    usleep(philo->params->time_to_eat * 1000);
	//pthread_mutex_unlock(&philo->params->write_mutex);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    safe_write(philo, " has put down the forks\n");
}

static void	sleep_and_think(t_philo *philo)
{
	safe_write(philo, " is sleeping\n");
	pthread_mutex_lock(&philo->params->write_mutex);
	usleep(philo->params->time_to_sleep * 1000);
	pthread_mutex_unlock(&philo->params->write_mutex);
	safe_write(philo, " is thinking\n");
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->params->num_philos == 1)
    {
        handle_single_philo(philo);
        return (NULL);
    }
    if (philo->params->max_meals == -1)
    {
        while (1)
        {
            take_forks(philo);
            eat(philo);
            sleep_and_think(philo);
        }
    }
    else
    {
        while (philo->num_meals < philo->params->max_meals)
        {
            take_forks(philo);
            eat(philo);
            philo->num_meals++;
            sleep_and_think(philo);
        }
        pthread_mutex_lock(&philo->params->all_eaten_mutex);
        philo->params->all_eaten++;
        pthread_mutex_unlock(&philo->params->all_eaten_mutex);

    }
    return (NULL);
}

void handle_single_philo(t_philo *philo)
{
    if (philo->params->num_philos == 1)
    {
        pthread_mutex_lock(philo->params->forks);
        safe_write(philo, " has taken a fork\n");
        usleep(philo->params->time_to_die * 1000);
        safe_write(philo, " has died\n");
        pthread_mutex_unlock(philo->params->forks);
    }
    return ;
}