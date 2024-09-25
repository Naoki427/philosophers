/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:21:54 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/09/25 18:10:42 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_all_philos(t_tool *tool)
{
	int	i;

	i = 0;
	while (i < tool->fork_num)
	{
		pthread_mutex_lock(&(tool->philos[i].meal));
		if (check_end(tool, i))
		{
			pthread_mutex_unlock(&(tool->philos[i].meal));
			break ;
		}
		pthread_mutex_unlock(&(tool->philos[i].meal));
		i++;
	}
}

int	check_end(t_tool *tool, int i)
{
	if (get_current_time() - tool->philos[i].state_time > tool->ttd)
	{
		pthread_mutex_lock(&(tool->alive_mutex));
		tool->philos_alive = 0;
		printf("%lld %d died\n", get_current_time() - tool->start_time, i + 1);
		pthread_mutex_unlock(&(tool->alive_mutex));
		return (1);
	}
	if (track_meals(tool, tool->philos, i))
	{
		pthread_mutex_lock(&(tool->alive_mutex));
		tool->philos_alive = 0;
		printf("%lld All the philosophers have eaten at least %ld times.\n",
			get_current_time() - tool->start_time, tool->eat_time);
		pthread_mutex_unlock(&(tool->alive_mutex));
		return (1);
	}
	return (0);
}

int	track_meals(t_tool *tool, t_philo *philos, int i)
{
	static int	count = 0;
	static int	flg[200] = {0};

	if (tool->fork_num == 1 || !tool->eat_time)
		return (0);
	if (philos[i].eat_time >= tool->eat_time && flg[i] == 0)
	{
		flg[i] = 1;
		count++;
		if (count == tool->fork_num)
			return (1);
	}
	return (0);
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
