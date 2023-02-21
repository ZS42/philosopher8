/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:51:50 by zsyyida           #+#    #+#             */
/*   Updated: 2023/02/21 13:23:58 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// to initialise mutex
// pthread_mutex_init(&mutex, NULL);

void	init_forks(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->n_of_philo)
	table->forks[i++] = 0;
}

void	init_mutexes(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->n_of_philo)
		pthread_mutex_init(&table->mutex[i++], NULL);
	i = 0;
	while (i < table->n_of_philo)
		pthread_mutex_init(&table->mutex_ids[i++], NULL);
	pthread_mutex_init(table->mutex_print, NULL);
	pthread_mutex_init(table->mutex_death, NULL);
	pthread_mutex_init(table->mutex_time, NULL);
}

void	init_philos(t_table *table)
{
	t_philo			*philo;
	unsigned int	i;

	philo = table->philo;
	i = 0;
	while (i < table->n_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].eat = 0;
		philo[i].state = 0;
		philo[i].time_last_ate = 0;
		philo[i].table = table;
		i++;
	}
}

t_table	*init_table_helper(t_table *table)
{
	t_philo	*philo;

	table->forks = ft_calloc(table->n_of_philo,
			sizeof(int));
	table->ids = ft_calloc(table->n_of_philo,
			sizeof(int));
	table->thread = ft_calloc(table->n_of_philo,
			sizeof(pthread_t));
	table->mutex = ft_calloc(table->n_of_philo,
			sizeof(pthread_mutex_t));
	table->mutex_ids = ft_calloc(table->n_of_philo,
			sizeof(pthread_mutex_t));
	table->mutex_print = ft_calloc(1, sizeof(pthread_mutex_t));
	table->mutex_death = ft_calloc(1, sizeof(pthread_mutex_t));
	table->mutex_time = ft_calloc(1, sizeof(pthread_mutex_t));
	philo = calloc(table->n_of_philo, sizeof(t_philo));
	if (!table->forks || !table->ids || !table->thread
		|| !table->mutex || !table->mutex_print)
		return (NULL);
	table->philo = philo;
	return (table);
}

t_table	*init_table(char **av)
{
	t_table	*table;

	table = calloc(1, sizeof(t_table));
	table->n_of_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->number_of_times_each_philosopher_eats = ft_atoi(av[5]);
	else
		table->number_of_times_each_philosopher_eats = -1;
	table->die = 0;
	table->start_time = 0;
	init_table_helper(table);
	return (table);
}
