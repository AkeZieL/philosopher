/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:39:40 by mbilly            #+#    #+#             */
/*   Updated: 2023/04/28 14:11:19 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->gen->death);
	if (philo->gen->philo_died == 0)
	{
		pthread_mutex_lock(&(philo->gen->mutex_print));
		printf("%lld ms %d %s\n", (ft_time() - philo->gen->start_time) ,philo->philo_id, str);
		pthread_mutex_unlock(&(philo->gen->mutex_print));
	}
	pthread_mutex_unlock(&(philo->gen->death));
}

void	philo_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	usleep(philo->gen->time_sleep * 1000);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->gen->fork[philo->fork_right]);
	pthread_mutex_lock(&philo->gen->fork[philo->fork_left]);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->eat));
	philo->nbr_ate++;
	philo->last_time_eat = ft_time();
	pthread_mutex_unlock(&(philo->eat));
	ft_print(philo, "is eating");
	usleep(philo->gen->time_eat * 1000);
	pthread_mutex_unlock(&philo->gen->fork[philo->fork_left]);
	pthread_mutex_unlock(&philo->gen->fork[philo->fork_right]);
}
