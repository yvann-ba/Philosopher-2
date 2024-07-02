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
		usleep(100);
		pthread_mutex_lock(philo->right_fork);
		safe_write(philo, " has taken the right fork\n");
		pthread_mutex_lock(philo->left_fork);
		safe_write(philo, " has taken the left fork\n");
	}
}

static void	eat(t_philo *philo)
{
	gettimeofday(&philo->last_meal, NULL);
	safe_write(philo, " is eating\n");
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	safe_write(philo, " has put down the forks\n");
	philo->num_meals++;
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
	while (philo->num_philos > 1)
	{
		take_forks(philo);
		eat(philo);
		if (philo->max_meals != -1 && philo->num_meals >= philo->max_meals)
			break;
		sleep_and_think(philo);
	}
	return (NULL);
}