/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:35:30 by mbilly            #+#    #+#             */
/*   Updated: 2023/04/28 14:14:01 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->gen->death);
		pthread_mutex_lock(&philo->eat);
		if (ft_time() - philo->last_time_eat > philo->gen->time_death)
		{
			pthread_mutex_unlock(&(philo->gen->death));
			pthread_mutex_unlock(&(philo->eat));
			pthread_mutex_lock(&(philo->eat));
			if (philo->nbr_ate == philo->gen->nbr_meal)
			{
				pthread_mutex_unlock(&(philo->eat));
				return (1);
			}
			pthread_mutex_unlock(&philo->eat);
			ft_print(philo, "is died");
			pthread_mutex_lock(&philo->gen->death);
			philo->gen->philo_died++;
			pthread_mutex_unlock(&philo->gen->death);
			return (1);
		}
		pthread_mutex_unlock(&philo->eat);
		pthread_mutex_unlock(&philo->gen->death);
		usleep(100);
	}
	return (0);
}

void	*action_philo(t_philo *philo)
{
	pthread_t th_death;

	pthread_create(&th_death, NULL, (void *)check_death, philo);
	while (1)
	{
		if (philo->philo_id % 2 == 1)
			usleep(5000);
		pthread_mutex_lock(&(philo->gen->death));
		if (philo->gen->philo_died != 0)
		{

			pthread_mutex_unlock(&(philo->gen->death));
			break ;
		}
		pthread_mutex_unlock(&(philo->gen->death));
		philo_eat(philo);
		pthread_mutex_lock(&(philo->eat));
		if (philo->nbr_ate == philo->gen->nbr_meal)
		{

			pthread_mutex_unlock(&(philo->eat));
			break ;
		}
		pthread_mutex_unlock(&(philo->eat));
		philo_sleep(philo);
		ft_print(philo, "is thinking");
	}
	pthread_join(th_death, NULL);
	return (0);
}

static void	ft_end(t_general *gen)
{
	int	i;

	i = -1;
	if (gen->nbr_of_philo > 1)
	{
		while (++i < gen->nbr_of_philo)
			pthread_join(gen->philo[i].thread, NULL);
	}
	i = -1;
	while (++i < gen->nbr_of_philo)
		pthread_mutex_destroy(&(gen->fork[i]));
	pthread_mutex_destroy(&(gen->mutex_print));
	pthread_mutex_destroy(&(gen->death));
	free(gen->fork);
	free(gen->philo);
}

void	ft_start(t_general *gen)
{
	int	i;

	i = -1;
	if (gen->nbr_of_philo == 1)
	{
		printf("%lld ms %d %s\n", (ft_time() - gen->start_time), gen->philo[0].philo_id, "has taken a fork");
		usleep(gen->time_death * 1000);
		printf("%lld ms %d %s\n", (ft_time() - gen->start_time), gen->philo[0].philo_id, "is died");
		ft_end(gen);
		return ;
	}
	while (++i < gen->nbr_of_philo)
	{
		pthread_create(&(gen->philo[i].thread), NULL, (void *)action_philo, &(gen->philo[i]));
	}
	ft_end(gen);
}
