/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:23:23 by zsyyida           #+#    #+#             */
/*   Updated: 2023/02/21 13:51:33 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_free(t_table *table)
{
	free(table->forks);
	free(table->ids);
	pthread_mutex_destroy(table->mutex);
	pthread_mutex_destroy(table->mutex_ids);
	pthread_mutex_destroy(table->mutex_print);
	pthread_mutex_destroy(table->mutex_death);
	pthread_mutex_destroy(table->mutex_time);
	free(table->thread);
	free(table->mutex);
	free(table->mutex_ids);
	free(table->mutex_print);
	free(table->mutex_death);
	free(table->mutex_time);
	free(table->philo);
	free(table);
}

long	ft_atoi(char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*mem;
	unsigned int	i;

	mem = malloc(count * size);
	if (!mem)
		return (0);
	i = 0;
	while (i < (count * size))
	{
		((unsigned char *)mem)[i] = '0';
		i++;
	}
	return (mem);
}

void	ft_print(t_philo *philo)
{
	unsigned int	time;

	pthread_mutex_lock(philo->table->mutex_death);
	if (philo->table->die != 0)
	{
		pthread_mutex_unlock(philo->table->mutex_death);
		return ;
	}
	else
		pthread_mutex_unlock(philo->table->mutex_death);
	pthread_mutex_lock(philo->table->mutex_time);
	time = ft_get_time() - philo->table->start_time;
	pthread_mutex_unlock(philo->table->mutex_time);
	pthread_mutex_lock(philo->table->mutex_print);
	if (philo->state == 1)
		printf("\x1b[36m%d %d %s\x1b[0m\n", time, philo->id, " is sleeping");
	else if (philo->state == 2)
		printf("\x1b[32m%d %d %s\x1b[0m\n", time, philo->id, "has taken forks");
	else if (philo->state == 3)
		printf("\x1b[35m%d %d %s\x1b[0m\n", time, philo->id, "is eating");
	pthread_mutex_unlock(philo->table->mutex_print);
}

//   gettimeofday(&end, NULL);
//   printf("Time taken to count to 10^5 is : %ld micro seconds\n",
//     ((end.tv_sec * 1000000 + end.tv_usec) -
//     (start.tv_sec * 1000000 + start.tv_usec)));
// int main() {
//   struct timeval current_time;
//   gettimeofday(&current_time, NULL);
//   printf("seconds : %ld\nmicro seconds : %ld",
//     current_time.tv_sec, current_time.tv_usec);
//   return 0;
// }

// Using gettimeofday in order to Measure Program Execution Time
// #include <sys/time.h>
// #include <stdio.h>

// gettimeofday takes two parameters as addresses struct timeval tv
// and struct timezone	tz (which is no longer used and is only passed
// as NULL for backwards compatibility)
// this stores the sec and microsec as tv_sec and tv_usec
// which need to be converted to millisec and added to get time as time_t
// printf("time in millisec %ld\n", t);
unsigned int	ft_get_time(void)
{
	struct timeval	tv;
	unsigned int	t;

	gettimeofday(&tv, NULL);
	t = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (t);
}
