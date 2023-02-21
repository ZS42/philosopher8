/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:23:08 by zsyyida           #+#    #+#             */
/*   Updated: 2023/02/21 15:30:47 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_update_eat(t_philo *philo, unsigned int id1, unsigned int id2)
{
	philo->eat += 1;
	pthread_mutex_lock(philo->table->mutex_time);
	philo->time_last_ate = ft_get_time();
	pthread_mutex_unlock(philo->table->mutex_time);
	pthread_mutex_lock(&philo->table->mutex_ids[id1]);
	philo->table->ids[id1] = philo->id;
	pthread_mutex_unlock(&philo->table->mutex_ids[id1]);
	pthread_mutex_lock(&philo->table->mutex_ids[id2]);
	philo->table->ids[id2] = philo->id;
	pthread_mutex_unlock(&philo->table->mutex_ids[id2]);
	return (0);
}

void	ft_drop_forks(t_philo *philo, unsigned int id1, unsigned int id2)
{
	pthread_mutex_lock(&philo->table->mutex[id2]);
	philo->table->forks[id2] = 0;
	pthread_mutex_unlock(&philo->table->mutex[id2]);
	pthread_mutex_lock(&philo->table->mutex[id1]);
	philo->table->forks[id1] = 0;
	pthread_mutex_unlock(&philo->table->mutex[id1]);
}

int	ft_eat(t_philo *philo, unsigned int id1, unsigned int id2)
{
	if (philo->eat - philo->table->number_of_times_each_philosopher_eats == 0)
		return (1);
	pthread_mutex_lock(philo->table->mutex_death);
	if (philo->table->die == 0)
	{
		pthread_mutex_unlock(philo->table->mutex_death);
		philo->state = 3;
		ft_print(philo);
		ft_wait(philo->table->time_to_eat, philo->table);
		ft_drop_forks(philo, id1, id2);
		if (ft_update_eat(philo, id1, id2) == 1)
			return (1);
		if (philo->eat != philo->table->number_of_times_each_philosopher_eats)
		{
			philo->state = 1;
			ft_print(philo);
			ft_wait(philo->table->time_to_sleep, philo->table);
		}
	}
	else
		pthread_mutex_unlock(philo->table->mutex_death);
	return (0);
}

int	ft_check_id(t_philo *philo, unsigned int id)
{
	pthread_mutex_lock(&philo->table->mutex_ids[id]);
	if (philo->id == philo->table->ids[id])
	{
		pthread_mutex_unlock(&philo->table->mutex_ids[id]);
		return (1);
	}
	else
		pthread_mutex_unlock(&philo->table->mutex_ids[id]);
	return (0);
}
