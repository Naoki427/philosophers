/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:42:59 by yoshiminaok       #+#    #+#             */
/*   Updated: 2024/09/25 18:30:08 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialize_tool(t_tool *tool, char **argv, int argc)
{
	tool->fork_num = philo_atol(argv[1]);
	tool->ttd = philo_atol(argv[2]);
	tool->tte = philo_atol(argv[3]);
	tool->tts = philo_atol(argv[4]);
	if (argc == 6)
		tool->eat_time = philo_atol(argv[5]);
	else
		tool->eat_time = 0;
	tool->index = 0;
	tool->philos_alive = 1;
	return (initialize_mutexes(tool));
}

int	initialize_mutexes(t_tool *tool)
{
	long	i;

	i = 0;
	tool->mutexes = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* tool->fork_num);
	if (!tool->mutexes)
		return (1);
	while (i < tool->fork_num)
	{
		pthread_mutex_init(&(tool->mutexes[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(tool->alive_mutex), NULL);
	pthread_mutex_init(&(tool->print_mutex), NULL);
	return (0);
}

long	philo_atol(const char *str)
{
	long	flg;
	long	num;

	flg = 1;
	num = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			flg *= -1;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = 10 * num + (*str - '0');
		str++;
	}
	return (flg * num);
}

int	initialize_philos(t_philo **philos, int num, t_tool *tool)
{
	int	i;

	i = 0;
	*philos = (t_philo *)malloc(sizeof(t_philo) * (num));
	if (!(*philos))
		return (1);
	while (i < num)
	{
		(*philos)[i].eat_time = 0;
		(*philos)[i].tool = tool;
		(*philos)[i].state_time = get_current_time();
		pthread_mutex_init(&(((*philos)[i]).meal), NULL);
		i++;
	}
	return (0);
}
