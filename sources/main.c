/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:03:21 by zsyyida           #+#    #+#             */
/*   Updated: 2023/02/21 13:23:14 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check(int ac, char **av)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (ac < 5 || ac > 6)
	{
		printf("Error: wrong number of arguments");
		return (1);
	}
	while (++i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
			{
				printf("Error: only digits as arguments");
				return (1);
			}
			else
				j++;
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	long	time;
	t_table	*table;

	if (check(ac, av) == 1)
		return (1);
	if (av[1][0] == '1' && av[1][1] == '\0')
	{
		time = ft_atoi(av[2]);
		usleep(time * 1000);
		printf("\x1b[31m%ld %d %s\x1b[0m\n", time, 1, "died");
		return (1);
	}
	table = init_table(av);
	init_philos(table);
	init_forks(table);
	init_mutexes(table);
	init_threads(table);
	ft_free(table);
}
