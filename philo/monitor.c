/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:21:54 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/09/19 13:41:20 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_all_philos(t_tool *tool)
{
	int	i;

	i = 0;
	while (i < tool->fork_num)
	{
		if (get_current_time() - tool->philos[i].state_time >= tool->ttd)
		{
			tool->philos_alive = 0;
			pthread_mutex_lock(&(tool->alive_mutex));
			printf("%lld %d died.\n", get_current_time() - tool->start_time, i
				+ 1);
			break ;
		}
		if (track_meals(tool, tool->philos))
		{
			tool->philos_alive = 0;
			pthread_mutex_lock(&(tool->alive_mutex));
			printf("%lld All the philosophers have eaten at least %ld times.\n",
				get_current_time() - tool->start_time, tool->eat_time);
			break ;
		}
		i++;
	}
	if (!tool->philos_alive)
		pthread_mutex_unlock(&(tool->alive_mutex));
}

int	track_meals(t_tool *tool, t_philo *philos)
{
	int	i;

	i = 0;
	if (!tool->eat_time)
		return (0);
	while (i < tool->fork_num)
	{
		if (philos[i].eat_time < tool->eat_time)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_tool	*tool;

	tool = (t_tool *)arg;
	while (tool->philos_alive)
	{
		usleep(3000);
		check_all_philos(tool);
	}
	return (NULL);
}
