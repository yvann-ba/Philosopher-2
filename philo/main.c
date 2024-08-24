#include "philo.h"

int monitor_philo(t_params *params)
{
    int end_simulation;

	end_simulation = 0;
    pthread_mutex_lock(&params->is_dead_mutex);
    if (params->is_dead == 1)
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

void join_philos(t_params *params)
{
	int i;

	i = 0;
	while (i < params->num_philos)
	{
		pthread_join(params->philo[i].thread, NULL);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_params *params;

	params = malloc(sizeof(t_params));
	if ((init_params(params, argc, argv) || init_forks(params) || init_philos(params)) == NULL)
		return (1);
	start_simulation(params, params->num_philos);
	monitor_philo(params);
	join_philos(params);
	cleanup(params);
	return (0);
}



















//print
// printf("Params:\n");
// printf("Number of Philosophers: %d\n", params->num_philos);
// printf("Time to Die: %d\n", params->time_to_die);
// printf("Time to Eat: %d\n", params->time_to_eat);
// printf("Time to Sleep: %d\n", params->time_to_sleep);
// printf("Max Meals (if applicable): %d\n", params->max_meals);
// printf("Is Dead: %d\n", params->is_dead);
// printf("Start Time: %lu\n", params->start_time);

// printf("\nForks:\n");
// for (int i = 0; i < params->num_philos; i++) {
// 	printf("Fork %d\n", i);
// }
// printf("\nPhilosophers:\n");
// for (int i = 0; i < params->num_philos; i++) {
// 	printf("Philosopher %d:\n", params->philo[i].id);
// 	printf("Last Meal: %lu\n", params->philo[i].last_meal);
// 	printf("Meals Eaten: %d\n", params->philo[i].num_meals);
// }

// int monitor_simulation(t_philo *philo)
// {
// 	unsigned long current_time;
// 	unsigned long time_since_last_meal;
// 	int i;

// 	while (1)
// 	{
// 		usleep(1000);
// 		i = 0;
// 		while (i < philo->params->num_philos)
//         {
//             current_time = get_current_time_in_ms();
//             pthread_mutex_lock(&philo[i]->meal_mutex);
//             time_since_last_meal = current_time - philo[i]->last_meal;
//             pthread_mutex_unlock(&philo[i]->meal_mutex);

//             if (time_since_last_meal >= (unsigned long)philo[i]->params->time_to_die)
//             {
//                 safe_write(philo[i], " has died\n");
//                 pthread_mutex_lock(&philo[i]->params->is_dead_mutex);
//                 philo[i]->params->is_dead = 1;
//                 pthread_mutex_unlock(&philo[i]->params->is_dead_mutex);
//                 return (1);
//             }
//         }
// 		pthread_mutex_lock(&philo->params->all_eaten_mutex);
// 		if (philo->params->all_eaten == philo->params->num_philos)
// 		{
// 			pthread_mutex_unlock(&philo->params->all_eaten_mutex);
// 			return (1);
// 		}
// 		pthread_mutex_unlock(&philo->params->all_eaten_mutex);
// 	}
// 	return (0);
// }

// if (time_since_last_meal == current_time)
// 	time_since_last_meal = 0;

//        pthread_mutex_lock(&philo->params->write_mutex);
//        printf("current time = %ld\nlast meal = %ld\ntime since last meal = %ld\ntime to die = %ld\n",
//               current_time, philo->last_meal, time_since_last_meal, (unsigned long)philo->params->time_to_die);
//        pthread_mutex_unlock(&philo->params->write_mutex);

// args:
//  1 number_of_philosophers
//  2 time_to_die
//  3 time_to_eat
//  4 time_to_sleep
//  5 [number_of_times_each_philosopher_must_eat]