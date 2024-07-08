
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
	int				id;
	int 			num_meals;
	pthread_t 		thread;
	pthread_mutex_t meal_mutex;
	unsigned long	last_meal;
	struct s_params *params;
	
} t_philo;

typedef struct s_params
{
	int				num_philos;
	int 			time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	int 			max_meals;
	unsigned long 	start_time;
	pthread_mutex_t	*forks;
	int				is_dead;
	pthread_mutex_t is_dead_mutex;
	pthread_mutex_t write_mutex;
	t_philo			*philo;
} t_params;

int 			check_args(int argc, char **argv);

//INIT
int				init_params(t_params *params, int argc, char **argv);
int				init_forks(t_params *params);
t_philo 		*init_philos(t_params *params);


int 			monitor_simulation(t_params *params);
int 			check_end(t_params *params);
void 			start_simulation(t_params *params, int num_philos);
void 			*monitor_routine(void *arg);
void 			*philo_routine(void *arg);
void			monitor_thread(t_params *params);

//UTILS
void 			ft_putnbr(int n);
void 			ft_putstr(char *str);
int 			ft_is_digit(char *str);
int				ft_atoi(const char *str);
void 			safe_write(t_philo *philo, char *msg);

//TIME
unsigned long 	get_current_time_in_ms();
long long		get_elapsed_time(long long start_time);
long long		get_current_time_in_us(void);
long long		get_current_time_in_us(void);
unsigned long 	get_current_time_in_ms(void);

//CLEAN || EXIT
void 			cleanup(t_philo *philo, pthread_mutex_t *forks, t_params *params);
int				error_handle(const char *msg, t_params *params);

#endif