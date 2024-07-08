#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
        if (!check_end(philo))
        {
            pthread_mutex_lock(philo->left_fork);
            safe_write(philo, " has taken the left fork\n");
            pthread_mutex_lock(philo->right_fork);
            safe_write(philo, " has taken the right fork\n");
        }
	}
	else
	{
        if (!check_end(philo))
        {
            usleep(1000);
            pthread_mutex_lock(philo->right_fork);
            safe_write(philo, " has taken the right fork\n");
            pthread_mutex_lock(philo->left_fork);
            safe_write(philo, " has taken the left fork\n");
        }
    }
}

static void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_current_time_in_ms();
    philo->num_meals++;
	if (philo->num_meals >= philo->params->max_meals && philo->params->max_meals != -1)
	{
		pthread_mutex_lock(&philo->params->all_eaten_mutex);
        philo->params->all_eaten++;
        pthread_mutex_unlock(&philo->params->all_eaten_mutex);
	}
    pthread_mutex_unlock(&philo->meal_mutex);
    safe_write(philo, " is eating\n");
	pthread_mutex_lock(&philo->params->write_mutex);
    usleep(philo->params->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->params->write_mutex);
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

int check_end(t_philo *philo)
{
    int end_simulation;

	end_simulation = 0;
    pthread_mutex_lock(&philo->params->is_dead_mutex);
    if (philo->params->is_dead == 1)
    {
        end_simulation = 1;
    }
    pthread_mutex_unlock(&philo->params->is_dead_mutex);
    pthread_mutex_lock(&philo->params->all_eaten_mutex);
    if (philo->params->all_eaten == philo->params->num_philos)
    {
        printf("Philo %d detected all_eaten\n", philo->id);

        end_simulation = 1;
    }
    pthread_mutex_unlock(&philo->params->all_eaten_mutex);

    return end_simulation;
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;


    while (!check_end(philo))
    {
        if (philo->params->num_philos == 1)
        {
            pthread_mutex_lock(philo->left_fork);
            safe_write(philo, " has taken the left fork\n");
            usleep(philo->params->time_to_die * 1000);
            safe_write(philo, " has died\n");
            pthread_mutex_unlock(philo->left_fork);
            break;
        }
        take_forks(philo);
        eat(philo);
        sleep_and_think(philo);
    }
    return (NULL);
}
