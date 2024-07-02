
#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>


typedef struct s_philo
{
	int	id;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int num_meals;
	int max_meals;
    pthread_t thread;
    pthread_t monitor_thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
	pthread_mutex_t *write_mutex;
	pthread_mutex_t meal_mutex;
	struct timeval last_meal;
	int num_philos;
	struct timeval start_time;
} t_philo;

typedef struct s_params
{
	int num_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int max_meals;
	unsigned long start_time;
} t_params;

// print_utils.c
void ft_putnbr(int n);
void ft_putstr(char *str);
void safe_write(t_philo *philo, char *msg);

//utils.c
int ft_is_digit(char *str);
int	ft_atoi(const char *str);
unsigned long get_time_in_ms(struct timeval start);

void cleanup(t_philo *philo, pthread_mutex_t *forks, pthread_mutex_t *write_mutex, int num_philos);


//check_args.c
int check_args(int argc, char **argv);

//init_philo.c
t_philo *init_philos(t_params *params, pthread_mutex_t *forks, pthread_mutex_t *write_mutex);
pthread_mutex_t *init_write_mutex(void);

//philo.c
void start_simulation(t_philo *philo, int num_philos);
void *monitor_routine(void *arg);
void *philo_routine(void *arg);
void	monitor_thread(t_philo *philo);


#endif