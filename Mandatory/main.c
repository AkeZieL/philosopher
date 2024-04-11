/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:24:55 by mbilly            #+#    #+#             */
/*   Updated: 2023/04/20 17:50:14 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_general	gen;

	if (argc < 5 || argc > 6 || check_error(&argv[1]) == 0)
	{
		wrong_input();
		return (0);
	}
	if (init_all(argc, argv, &gen) == 0)
		return (0);
	ft_start(&gen);
}
