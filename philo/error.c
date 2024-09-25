/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:42:44 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/09/22 23:29:38 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_input(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		write(2, "Error:Incorrect number of arguments.\n", 37);
		return (1);
	}
	while (i < argc)
	{
		if (check_valid_num(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_num(char *arg)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	while (arg[i])
	{
		if ((arg[i] < '0' || arg[i] > '9') || (i == 0 && arg[i] == '0'))
		{
			write(2, "Error:Non-positive or non-numeric characters detected.\n",
				55);
			return (1);
		}
		if ((LONG_MAX - (arg[i] - '0')) / 10 < num)
		{
			write(2, "Error:The number is too large.\n", 31);
			return (1);
		}
		num = 10 * num + (arg[i] - '0');
		i++;
	}
	return (0);
}
