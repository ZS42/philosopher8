/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:56:23 by zsyyida           #+#    #+#             */
/*   Updated: 2023/02/21 14:04:48 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// for threads
# include <pthread.h>
// for printf
# include <stdio.h>
// for malloc
# include <stdlib.h>
// for usleep
# include <unistd.h>
// for gettimeofday
# include <sys/time.h>
// for memset
# include <string.h>

typedef struct s_table
{
	unsigned int	n_of_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_times_each_philosopher_eats;
	unsigned int	die;
	unsigned int	start_time;
	unsigned int	*forks;
	unsigned int	*ids;
	pthread_t		*thread;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*mutex_ids;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*mutex_death;
	pthread_mutex_t	*mutex_time;
	struct s_philo	*philo;
}	t_table;

// state = 0 starting, 1 = sleeping, 2 = taking fork,
// 	 3 = eating, 4 = thinking. 5 = dead
typedef struct s_philo
{
	unsigned int	id;
	unsigned int	eat;
	unsigned int	state;
	unsigned int	time_last_ate;
	t_table			*table;
}	t_philo;

void			*routine(void *param);
long			ft_atoi(char *str);
t_table			*init_table(char **av);
t_table			*init_table_helper(t_table *table);
void			init_philos(t_table *table);
void			init_threads(t_table *table);
void			init_mutexes(t_table *table);
void			init_forks(t_table *table);
void			*ft_calloc(size_t count, size_t size);
void			ft_print(t_philo *philo);
unsigned int	ft_get_time(void);
void			ft_start(t_philo *philo);
int				ft_take_forks_helper(t_philo *philo, unsigned int id1,
					unsigned int id2);
int				ft_take_forks_helper2(t_table *table, t_philo *philo,
					unsigned int id1, unsigned int id2);
int				ft_take_forks(t_philo *philo);
void			ft_drop_forks(t_philo *philo, unsigned int id1,
					unsigned int id2);
int				ft_eat(t_philo *philo, unsigned int id1, unsigned int id2);
int				ft_update_eat(t_philo *philo, unsigned int id1,
					unsigned int id2);
void			ft_even_philo(t_philo *philo);
void			ft_free(t_table *table);
int				ft_wait(unsigned int time, t_table *table);
int				ft_think(t_philo *philo);
int				ft_check_death(t_philo *philo);
int				ft_check_death_helper(t_philo *philo, unsigned int time,
					unsigned int print_time);
int				ft_check_id(t_philo *philo, unsigned int id);

#endif