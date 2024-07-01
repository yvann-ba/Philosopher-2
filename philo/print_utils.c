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
	unsigned long current_time = get_time_in_ms(philo->start_time);

	pthread_mutex_lock(philo->write_mutex);
	ft_putnbr(current_time);
	ft_putstr(" ");
	ft_putnbr(philo->id);
	ft_putstr(msg);
	pthread_mutex_unlock(philo->write_mutex);
}
//void safe_write(t_philo philo, char *msg)
//{
//	unsigned long current_time = get_time_in_ms();



//	pthread_mutex_lock();
//    printf("%lu ", current_time);
//    printf("%d", id);
//    printf("%s", msg);
//	pthread_mutex_unlock(write_mutex);
//}
