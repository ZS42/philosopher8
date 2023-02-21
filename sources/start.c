/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:08:06 by zsyyida           #+#    #+#             */
/*   Updated: 2023/02/21 15:28:52 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// unsigned int i = 0;
// 	pthread_mutex_lock(philo->table->mutex_print);
// 	while (i < philo->table->n_of_philo
// 	{
// 		printf("%d ",philo->table->forks[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	pthread_mutex_unlock(philo->table->mutex_print);

int	ft_take_forks_helper2(t_table *table, t_philo *philo,
	unsigned int id1, unsigned int id2)
{
	pthread_mutex_lock(&table->mutex[id1]);
	if (table->forks[id1] == 0)
	{
		table->forks[id1] = 1;
		pthread_mutex_unlock(&table->mutex[id1]);
		pthread_mutex_lock(&table->mutex[id2]);
		if (table->forks[id2] == 0)
		{
			table->forks[id2] = 1;
			pthread_mutex_unlock(&table->mutex[id2]);
			philo->state = 2;
			ft_print(philo);
			ft_eat(philo, id1, id2);
		}
		else
		{
			pthread_mutex_unlock(&table->mutex[id2]);
			pthread_mutex_lock(&table->mutex[id1]);
			table->forks[id1] = 0;
			pthread_mutex_unlock(&table->mutex[id1]);
		}
	}
	else
		pthread_mutex_unlock(&table->mutex[id1]);
	return (0);
}

int	ft_take_forks_helper(t_philo *philo,
		unsigned int id1, unsigned int id2)
{
	t_table			*table;

	table = philo->table;
	if ((ft_check_id(philo, id1) == 1) || (ft_check_id(philo, id2) == 1))
		return (1);
	ft_take_forks_helper2(table, philo, id1, id2);
	return (0);
}

// need to use locks and scheduling to prevent a dealock.
// this is called atomic locking
// can use a queue an array to store last philo that used a certain fork id and
// ate so it can't take it again to make sure same philosopher doesnt keep
//  getting a chance leaving another one out.
// to prevent deadlock use min fork first and max second.
//  Dont use % wont work for second last philo
// last philo is seperate bc uses other that id - 1  and id - 2 fork
int	ft_take_forks(t_philo *philo)
{
	if (philo->id == 1)
	{
		if (ft_take_forks_helper(philo, 0, (philo->table->n_of_philo - 1)) == 1)
			return (1);
	}
	else
		if (ft_take_forks_helper(philo, (philo->id - 2), (philo->id - 1)) == 1)
			return (1);
	return (0);
}

void	ft_start(t_philo *philo)
{
	if (philo->table->n_of_philo % 2 == 0)
		ft_even_philo(philo);
	else
	{
		ft_take_forks(philo);
		if (philo->table->number_of_times_each_philosopher_eats
			- philo->eat != 0)
			ft_think(philo);
	}
}

void	*routine(void *p)
{
	t_philo			*philo;

	philo = (t_philo *)p;
	philo->time_last_ate = ft_get_time();
	while (1)
	{
		ft_start(philo);
		if (philo->table->number_of_times_each_philosopher_eats
			== philo->eat)
			break ;
		pthread_mutex_lock(philo->table->mutex_death);
		if (philo->table->die == 1)
		{
			pthread_mutex_unlock(philo->table->mutex_death);
			break ;
		}
		else
			pthread_mutex_unlock(philo->table->mutex_death);
	}
	return (NULL);
}
