
#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

struct	s_philo;
struct	s_params;


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

typedef struct s_params
{
	int num_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int max_meals;
	int	all_eaten;
	pthread_mutex_t all_eaten_mutex;
	int is_dead;
	pthread_mutex_t is_dead_mutex;
	pthread_mutex_t write_mutex;
	unsigned long start_time;
	t_philo *philo;
} t_params;

void ft_putnbr(int n);
void ft_putstr(char *str);
void safe_write(t_philo *philo, char *msg);


int ft_is_digit(char *str);
int	ft_atoi(const char *str);

void cleanup(t_philo *philo, pthread_mutex_t *forks, t_params *params);
int	init_params(t_params *params, int argc, char **argv);
int	init_resources(t_params *params, pthread_mutex_t **forks);

unsigned long get_current_time_in_ms();
long long	get_elapsed_time(long long start_time);
long long	get_current_time_in_us(void);
long long	get_current_time_in_us(void);
unsigned long get_current_time_in_ms(void);

int monitor_simulation(t_philo *philo);
long long	get_elapsed_time(long long start_time);
int check_args(int argc, char **argv);

t_philo *init_philos(t_params *params, pthread_mutex_t *forks);

void start_simulation(t_philo *philo, int num_philos);
void *monitor_routine(void *arg);
void *philo_routine(void *arg);
void	monitor_thread(t_philo *philo);


#endif