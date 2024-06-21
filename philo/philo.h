
#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


typedef struct s_philo
{
	int	id;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int num_meals;
	int max_meals;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
} t_philo;

typedef struct s_params
{
	int num_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int max_meals;
} t_params;

typedef struct s_forks
{
	pthread_mutex_t *forks;
} t_forks;

int ft_is_digit(char *str);
int	ft_atoi(const char *str);
int check_args(int argc, char **argv);

t_philo *init_philos(t_params *params, t_forks *forks);
void init_philo_data(t_philo *philo, int id, t_params *params, t_forks *forks);
void *philo_routine(void *arg);
void start_simulation(t_philo *philo, int num_philos);

#endif