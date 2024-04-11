/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:12:48 by mbilly            #+#    #+#             */
/*   Updated: 2023/04/27 16:21:42 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int	signe;
	int	res;

	signe = 1;
	res = 0;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signe = -1;
		nptr++;
	}
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	return (res * signe);
}

long long	ft_time(void)
{
	struct timeval	res;

	gettimeofday(&res, NULL);
	return (res.tv_sec * 1000 + res.tv_usec / 1000);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	wrong_input(void)
{
	write(1, "\033[31mWrong input\n\n\033[0m", \
			ft_strlen("\033[31mWrong input\n\n\033[0m"));
	write(1, "\033[32m./philo\nnumber_of_philosophers >= 1,\n", \
			ft_strlen("\033[32m./philo\nnumber_of_philosophers >= 1,\t"));
	write(1, "time_to_die >= 0,\ntime_to_eat >= 0,\n", \
			ft_strlen("time_to_die >= 0,\tttime_to_eat >= 0,\t"));
	write(1, "time_to_sleep >= 0,\n(optionnel) ", \
			ft_strlen("time_to_sleep >= 0,\t(optionnel) "));
	write(1, "number_of_times_each_philosopher_must_eat >= 0 Ou -1 pour infini,\n\033[0m", \
			ft_strlen("number_of_times_each_philosopher_must_eat >= 0 Ou -1 pour infini,\n\033[0m"));
}
