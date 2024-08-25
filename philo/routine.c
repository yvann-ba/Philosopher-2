#include "philo.h"

static void	take_forks(t_philo *philo)
{
    int right_fork;
	int left_fork;

	if (!philo->params || !philo)
		return ;
	right_fork = 0;
	left_fork = 0;
	right_fork = (philo->id + 1) % philo->params->num_philos;
	left_fork = philo->id;
 
     if (philo->id % 2 == 0)
     {
        pthread_mutex_lock(&philo->params->forks[right_fork]);
        safe_write(philo, " has taken a fork\n");
        pthread_mutex_lock(&philo->params->forks[left_fork]);
        safe_write(philo, " has taken a fork\n");
    } 
    else
    {
        pthread_mutex_lock(&philo->params->forks[left_fork]);
        safe_write(philo, " has taken a fork\n");
        pthread_mutex_lock(&philo->params->forks[right_fork]);
        safe_write(philo, " has taken a fork\n");
    }

}

static void eat(t_philo *philo)
{
	if (!philo->params || !philo)
		return 
    pthread_mutex_lock(&philo->params->meal_mutex);
	philo->last_meal = get_current_time_in_ms();
    philo->num_meals++;
    if (philo->num_meals == philo->params->max_meals)
    {
        pthread_mutex_lock(&philo->params->all_eaten_mutex);
        philo->params->all_eaten++;
        pthread_mutex_unlock(&philo->params->all_eaten_mutex);
    
    }
    pthread_mutex_unlock(&philo->params->meal_mutex);

    safe_write(philo, " is eating\n");
    usleep(philo->params->time_to_eat * 1000);

    if (philo->id % 2 == 0)
    {
        pthread_mutex_unlock(&philo->params->forks[(philo->id + 1) % philo->params->num_philos]);
        pthread_mutex_unlock(&philo->params->forks[philo->id]);
    }
    else
    {
        pthread_mutex_unlock(&philo->params->forks[philo->id]);
        pthread_mutex_unlock(&philo->params->forks[(philo->id + 1) % philo->params->num_philos]);
    }
    safe_write(philo, " has put down the forks\n");
}

static void	sleep_and_think(t_philo *philo)
{
    if (!philo->params || !philo)
		return ;
	safe_write(philo, " is sleeping\n");
	usleep(philo->params->time_to_sleep * 1000);
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
    else
    {
        if (philo->id % 2 == 0)
            usleep(10000);  
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
                sleep_and_think(philo);
            }
            pthread_mutex_lock(&philo->params->all_eaten_mutex);
            philo->params->all_eaten++;
            pthread_mutex_unlock(&philo->params->all_eaten_mutex);

        }
    }
    return (NULL);
}

void handle_single_philo(t_philo *philo)
{
        safe_write(philo, " has taken a fork\n");
        usleep(philo->params->time_to_die * 1000);
        safe_write(philo, " died\n");
        pthread_mutex_lock(&philo->params->is_dead_mutex);
        philo->params->is_dead = 1;
        pthread_mutex_unlock(&philo->params->is_dead_mutex);
    return ;
}