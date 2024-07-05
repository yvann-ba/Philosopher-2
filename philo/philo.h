
#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

struct	s_data;
struct	s_threads;

typedef struct s_params
{
	int num_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int max_meals;
	int	all_eaten;
	pthread_mutex_t all_eaten_mutex;
	int is_died;
	pthread_mutex_t is_died_mutex;
	pthread_mutex_t write_mutex;
	unsigned long start_time;
	t_philo *philo;
} t_params;

typedef struct s_philo
{
	int	id;
	int num_meals;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
	pthread_mutex_t meal_mutex;
	unsigned long last_meal;
	struct s_params *params;
	
} t_philo;

void ft_putnbr(int n);
void ft_putstr(char *str);
void safe_write(t_philo *philo, char *msg);


int ft_is_digit(char *str);
int	ft_atoi(const char *str);

void cleanup(t_philo *philo, pthread_mutex_t *forks, pthread_mutex_t *write_mutex, t_params *params);

unsigned long get_current_time_in_ms();
long long	get_elapsed_time(long long start_time);
long long	get_current_time_in_us(void);


int check_args(int argc, char **argv);

t_philo *init_philos(t_params *params, pthread_mutex_t *forks, pthread_mutex_t *write_mutex);
pthread_mutex_t *init_write_mutex(void);

void start_simulation(t_philo *philo, int num_philos);
void *monitor_routine(void *arg);
void *philo_routine(void *arg);
void	monitor_thread(t_philo *philo);


#endif