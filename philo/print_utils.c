#include "philo.h"

void ft_putnbr(int n)
{
    char c;
    
    if (n >= 10)
        ft_putnbr(n / 10);
    c = '0' + (n % 10);
    write(STDOUT_FILENO, &c, 1);
}

void ft_putstr(char *str)
{
    while (*str)
        write(STDOUT_FILENO, str++, 1);
}


void safe_write(t_philo *philo, char *msg)
{
	unsigned long current_time;

	pthread_mutex_lock(&philo->params->write_mutex);
    current_time = get_elapsed_time((long long)philo->params->start_time);
	ft_putnbr(current_time);
	ft_putstr(" ");
	ft_putnbr(philo->id);
	ft_putstr(msg);
    // ft_putstr(" ");
	// ft_putnbr(philo->num_meals);
    // ft_putstr(" meal");

	pthread_mutex_unlock(&philo->params->write_mutex);
}
