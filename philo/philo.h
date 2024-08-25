
#ifndef PHILO_H
# define PHILO_H

//COLORS--------------------
#define BLACK	"\033[0;30m"
#define RED		"\033[0;31m"
#define GREEN	"\033[0;32m"
#define YELLOW	"\033[0;33m"
#define BLUE	"\033[0;34m"
#define MAGENTA	"\033[0;35m"
#define CYAN	"\033[0;36m"
#define WHITE	"\033[0;37m"

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
	long long		last_meal;

	pthread_t 		thread;
	struct s_params *params;
	
} t_philo;

typedef struct s_params
{	
	int 			time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	int				num_philos;

	int				all_eaten;
	pthread_mutex_t all_eaten_mutex;

	int 			max_meals;
	pthread_mutex_t meal_mutex;
	
	long long 		start_time;

	int				is_dead;
	pthread_mutex_t is_dead_mutex;
	
	pthread_mutex_t write_mutex;
	pthread_mutex_t	*forks;
	
	t_philo			*philo;
} t_params;

//PARSING
int 			check_args(int argc, char **argv);

//INIT
int				init_params(t_params *params, int argc, char **argv);
int				init_forks(t_params *params);
t_philo 		*init_philos(t_params *params);

//PHILOSOPHERS
int				monitor_philo(t_params *params);
void 			start_simulation(t_params *params, int num_philos);
void 			*philo_routine(void *arg);
void			handle_single_philo(t_philo *philo);

//UTILS
void 			ft_putnbr(int n);
void 			ft_putstr(char *str);
int 			ft_is_digit(char *str);
int				ft_atoi(const char *str);
void 			safe_write(t_philo *philo, char *msg);

//TIME
long long 		get_current_time_in_ms(void);
long long		get_elapsed_time(long long start_time);

//CLEANUP
void			join_philos(t_params *params);
int				error_handle(const char *msg, t_params *params);
void			free_params(t_params *params);
void			free_forks(t_params *params);
int				clean_exit(t_params *params);

#endif