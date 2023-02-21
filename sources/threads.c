/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:26:44 by zsyyida           #+#    #+#             */
/*   Updated: 2023/02/21 15:05:04 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// // to start thread loop that executes a function
// if (pthread_create(&th[i], NULL, &function, NULL) != 0)
// 	return (-1);
// // if (pthread_create(&p1, NULL, &function, NULL(if no args)) != 0)
// // 	return (-1);
// // to wait for thread to finish
// if (pthread_join(th, NULL) != 0)
// 	return (-2);
// if (pthread_join(p1, NULL(if function
// called by pthread returns nothing)) != 0)
// 	return (-2);
// to destroy mutex
// pthread_mutex_destroy(&mutex);
// when creating threads in a loop.
// 1make an array of p_thread the size of the number of threads you want
// pthread_t th[8]. 8 is an example of number of threads
// 2 initiailize the mutex once at beginning
// 3 then use a loop to create all th ethreads with pthread_create
// using &th[i] or th +i as refereence
// 4 use a seperate loop to wait using pthread_join using th[i] instead of p1
// must be seperate loop for both otherwise will
//  create/destroy/create/destroy/etc
// instead of threads running together in parallel
// 5 then use pthread_mutex_destroy to destroy mutex

// usleep stops a thread for the number of microseconds passed to it
// timestamp and time in arguments is in milliseconds. Use to let all threads
// before movng on

// initialise structs,forks, mutexes, threads(philosophers)
//  run loops for create mutexes, create threads,
//  join threads, destroy mutexes
void	init_threads(t_table *table)
{
	unsigned int	i;

	table->start_time = ft_get_time();
	i = 0;
	while (table->n_of_philo > i)
	{
		if (pthread_create(&table->thread[i], NULL, &routine,
				(void *)&table->philo[i]) != 0)
		{
			printf("Error: thread not created\n");
			return ;
		}
		usleep(100);
		i++;
	}
	i = 0;
	while (i < table->n_of_philo)
	{
		if (pthread_join(table->thread[i], NULL) != 0)
		{
			printf("Error: thread not waited for %d\n", i);
			return ;
		}
		i++;
	}
}
