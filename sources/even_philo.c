/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:03:54 by zsyyida           #+#    #+#             */
/*   Updated: 2023/02/21 16:04:17 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_check_death_helper(t_philo *philo, unsigned int time,
	unsigned int print_time)
{
	pthread_mutex_lock(philo->table->mutex_time);
	print_time = ft_get_time() - philo->table->start_time;
	time = ft_get_time() - philo->time_last_ate;
	if (philo->table->time_to_die <= time)
	{
		pthread_mutex_unlock(philo->table->mutex_time);
		pthread_mutex_lock(philo->table->mutex_print);
		if (philo->state != 5)
			printf("\x1b[31m%d %d %s\x1b[0m\n", print_time, philo->id, "died");
		pthread_mutex_unlock(philo->table->mutex_print);
		philo->state = 5;
		pthread_mutex_lock(philo->table->mutex_death);
		philo->table->die = 1;
		pthread_mutex_unlock(philo->table->mutex_death);
		return (1);
	}
	else
		pthread_mutex_unlock(philo->table->mutex_time);
	return (0);
}

int	ft_check_death(t_philo *philo)
{
	unsigned int	time;
	unsigned int	print_time;

	time = 0;
	print_time = 0;
	pthread_mutex_lock(philo->table->mutex_death);
	if (philo->table->die == 1)
	{
		pthread_mutex_unlock(philo->table->mutex_death);
		return (1);
	}
	else
		pthread_mutex_unlock(philo->table->mutex_death);
	ft_check_death_helper(philo, time, print_time);
	return (0);
}

int	ft_wait(unsigned int time, t_table *table)
{
	unsigned int	begin;

	begin = ft_get_time();
	while (1)
	{
		if (ft_check_death(table->philo) == 1)
			{printf("%d %d\n",ft_get_time() - begin, table->die);
			return (42);}
		if ((ft_get_time() - begin) >= time)
		{
			return (1);
		}
		usleep(100);
	}
	return (0);
}

void	ft_even_philo(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		if (philo->eat == 0)
			ft_take_forks(philo);
	}
	else if (philo->id % 2 == 0)
	{
		if (philo->eat == 0)
		{
			usleep(philo->table->time_to_eat * 1000);
			ft_take_forks(philo);
		}
	}
	ft_take_forks(philo);
	if (philo->table->number_of_times_each_philosopher_eats
		- philo->eat != 0)
		ft_think(philo);
	return ;
}

int	ft_think(t_philo *philo)
{
	unsigned int	time;

	pthread_mutex_lock(philo->table->mutex_death);
	if (philo->table->die != 0)
	{
		pthread_mutex_unlock(philo->table->mutex_death);
		return (1);
	}
	else
		pthread_mutex_unlock(philo->table->mutex_death);
	pthread_mutex_lock(philo->table->mutex_time);
	time = ft_get_time() - philo->table->start_time;
	pthread_mutex_unlock(philo->table->mutex_time);
	pthread_mutex_lock(philo->table->mutex_print);
	if (philo->state != 4)
		printf("\x1b[33m%d %d %s\x1b[0m\n", time, philo->id, " is thinking");
	pthread_mutex_unlock(philo->table->mutex_print);
	philo->state = 4;
	usleep(100);
	return (0);
}
