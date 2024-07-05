#include "philo.h"

int check_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->simulation_mutex);
	if (!philo->params->simulation_running)
	{
		pthread_mutex_unlock(&philo->params->simulation_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->params->simulation_mutex);
	return (0);
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (check_end(philo))
			return ;
		pthread_mutex_lock(philo->left_fork);
		safe_write(philo, " has taken the left fork\n");
		pthread_mutex_lock(philo->right_fork);
		safe_write(philo, " has taken the right fork\n");
	}
	else
	{
		if (check_end(philo))
			return ;
		pthread_mutex_lock(philo->right_fork);
		safe_write(philo, " has taken the right fork\n");
		pthread_mutex_lock(philo->left_fork);
		safe_write(philo, " has taken the left fork\n");
	}
}

static void eat(t_philo *philo)
{
	if (check_end(philo))
		return ;
    pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_in_ms2();
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
	if (check_end(philo))
		return ;
	safe_write(philo, " is sleeping\n");
	pthread_mutex_lock(philo->write_mutex);
	usleep(philo->time_to_sleep * 1000);
	pthread_mutex_unlock(philo->write_mutex);
	safe_write(philo, " is thinking\n");
}



void *monitor_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    unsigned long current_time;
    unsigned long time_since_last_meal;

    while (1)
    {
        usleep(1000);
        pthread_mutex_lock(&philo->meal_mutex);
        current_time = get_time_in_ms2();
        time_since_last_meal = current_time - philo->last_meal;
		if (time_since_last_meal == current_time)
			time_since_last_meal = 0;

        printf("current time = %ld\nlast meal = %ld\ntime since last meal = %ld\ntime to die = %ld\n", 
               current_time, philo->last_meal, time_since_last_meal, (unsigned long)philo->time_to_die);
        if (time_since_last_meal >= (unsigned long)philo->time_to_die ||  philo->num_meals >= philo->max_meals)
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
void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {
        pthread_mutex_lock(&philo->params->simulation_mutex);
		monitor_routine(philo);
		if (!philo->params->simulation_running)
		{
			printf("\nf\n");
		    pthread_mutex_unlock(&philo->params->simulation_mutex);
            break;
		}
        pthread_mutex_unlock(&philo->params->simulation_mutex);
        take_forks(philo);
		if (check_end(philo))
			return (NULL);
        eat(philo);
		if (check_end(philo))
			return (NULL);
        sleep_and_think(philo);
		if (check_end(philo))
			return (NULL);
    }
    return NULL;
}