#include "philo.h"

//millisecondes
long long get_current_time_in_ms()
{
	struct timeval	tv;
	long long		current_time;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000LL + tv.tv_usec / 1000LL);
	return (current_time);
}

unsigned long get_time_in_ms()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

long long	get_elapsed_time(long long start_time)
{
	long long	elapsed_time;

	elapsed_time = get_current_time_in_ms() - start_time;
	return (elapsed_time);
}
