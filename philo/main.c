#include "philo.h"
// args:
//  1 number_of_philosophers
//  2 time_to_die
//  3 time_to_eat
//  4 time_to_sleep
//  5 [number_of_times_each_philosopher_must_eat]
int main(int argc, char **argv)
{
	t_params params;
	t_forks forks;
	t_philo *philo;

	if (check_args(argc, argv))
		return (1);
	params.num_philos = ft_atoi(argv[1]);
	params.time_to_die = ft_atoi(argv[2]);
	params.time_to_eat = ft_atoi(argv[3]);
	params.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params.max_meals = ft_atoi(argv[5]);
	else
		params.max_meals = -1;
	
	philo = init_philos(&params, &forks);
	if (!philo)
	{
		printf("Error: Failed to initialize philosophers\n");
		return (1);
	}
	start_simulation(philo, params.num_philos);
	free(philo);
	free(forks.forks);
	return (0);
}
