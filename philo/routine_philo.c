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

static void	eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->meal_mutex);
	gettimeofday(&philo->last_meal, NULL);
	philo->num_meals++;
    pthread_mutex_unlock(&philo->meal_mutex);
	safe_write(philo, " is eating\n");
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	safe_write(philo, " has put down the forks\n");
}

static void	sleep_and_think(t_philo *philo)
{
	safe_write(philo, " is sleeping\n");
	usleep(philo->time_to_sleep * 1000);
	safe_write(philo, " is thinking\n");
	usleep(100);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	monitor_thread(philo);
    while (philo->num_philos > 1 && (philo->max_meals == -1 || philo->num_meals < philo->max_meals))
    {
        take_forks(philo);
        eat(philo);
        sleep_and_think(philo);
    }
	return (NULL);
}