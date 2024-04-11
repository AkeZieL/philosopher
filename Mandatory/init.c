/* *********************o***************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:29:51 by mbilly            #+#    #+#             */
/*   Updated: 2023/04/28 14:16:49 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_mutex(t_general *gen)
{
	int	i;
	
	i = -1;
	while (++i < gen->nbr_of_philo)
	{
		pthread_mutex_init(&(gen->philo[i].eat), NULL);
		pthread_mutex_init(&(gen->philo[i].continu), NULL);	
		pthread_mutex_init(&(gen->fork[i]), NULL);
	}
	pthread_mutex_init(&gen->mutex_print, NULL);
	pthread_mutex_init(&(gen->death), NULL);
}

static void	init_philo_fork(t_general *gen, int i)
{
	if (i % 2 == 0)
	{
		gen->philo[i].fork_left = i;
		gen->philo[i].fork_right = (i + 1) % gen->nbr_of_philo;
	}
	else
	{
		gen->philo[i].fork_left = (i + 1) % gen->nbr_of_philo;
		gen->philo[i].fork_right = i;
	}
}

static void	init_philo(t_general *gen)
{
	int	i;

	i = -1;
	while (++i < gen->nbr_of_philo)
	{
		gen->philo[i].gen = gen;
		gen->philo[i].philo_id = i + 1;
		gen->philo[i].nbr_ate = 0;
		gen->philo[i].last_time_eat = ft_time();
		init_philo_fork(gen, i);
	}
}

static void	init_general(int ac, char **av, t_general *gen)
{
	gen->nbr_of_philo = ft_atoi(av[1]);
	gen->time_death = ft_atoi(av[2]);
	gen->time_eat = ft_atoi(av[3]);
	gen->time_sleep = ft_atoi(av[4]);
	if (ac == 5)
		gen->nbr_meal = -1;
	else
		gen->nbr_meal = ft_atoi(av[5]);
	gen->fork = (pthread_mutex_t *)malloc(gen->nbr_of_philo * sizeof(pthread_mutex_t));
	gen->philo = (t_philo *)malloc(gen->nbr_of_philo * sizeof(t_philo));
	gen->philo_died = 0;
	gen->start_time = ft_time();
}

int	init_all(int ac, char **av, t_general *gen)
{
	init_general(ac, av, gen);
	if (gen->nbr_of_philo < 1 || gen->time_death < 0 || gen->time_eat < 0 \
		       	|| gen->time_sleep < 0 || gen->nbr_meal < -1)
	{
		wrong_input();
		return (0);
	}
	init_philo(gen);
	init_mutex(gen);
	return (1);
}
