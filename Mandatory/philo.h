/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:26:26 by mbilly            #+#    #+#             */
/*   Updated: 2023/04/28 11:11:11 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <pthread.h>
# include <stddef.h>
# include <sys/time.h>

# define COLOR 0xFF0000

typedef struct	s_philo
{
	struct s_general	*gen;
	pthread_t	thread;
	pthread_mutex_t	eat;
	pthread_mutex_t	continu;
	int	nbr_ate;
	int	philo_id;
	int	fork_right;
	int	fork_left;
	long long	last_time_eat;
}t_philo;

typedef struct	s_general
{
	pthread_mutex_t	*fork;
	pthread_mutex_t mutex_print;
	pthread_mutex_t death;
	int	nbr_of_philo;
	int	time_eat;
	int	time_death;
	int	time_sleep;
	int	nbr_meal;
	int	philo_died;
	long long	start_time;
	t_philo	*philo;
}t_general;

int	check_error(char **av);
int	ft_isdigit(char c);
int	ft_atoi(const char *nptr);
int	init_all(int ac, char **av, t_general *gen);
int	check_death(t_philo *philo);
void	wrong_input(void);
void	ft_print(t_philo *philo, char *str);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	*action_philo(t_philo *philo);
void	ft_start(t_general *gen);
long long	ft_time(void);

#endif
