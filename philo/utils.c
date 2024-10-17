/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:25:53 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/09/25 19:38:09 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_statetime(t_tool *tool, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < tool->fork_num)
	{
		philo[i].state_time = tool->start_time;
		i++;
	}
}

void	put_message(char *message, long num, t_tool *tool)
{
	pthread_mutex_lock(&(tool->alive_mutex));
	if (!tool->philos_alive)
	{
		pthread_mutex_unlock(&(tool->alive_mutex));
		return ;
	}
	printf(message, get_current_time() - tool->start_time, num);
	pthread_mutex_unlock(&(tool->alive_mutex));
}

long long	get_current_time(void)
{
	struct timeval	tv;
	long long		result;

	gettimeofday(&tv, NULL);
	result = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);
	return (result);
}

void	precise_usleep(long long sleep_time, t_tool *tool)
{
	long long	now;

	now = get_current_time();
	while (1)
	{
		usleep(50);
		if (get_current_time() - now >= sleep_time)
			break ;
		pthread_mutex_lock(&(tool->alive_mutex));
		if (!tool->philos_alive)
		{
			pthread_mutex_unlock(&(tool->alive_mutex));
			break ;
		}
		pthread_mutex_unlock(&(tool->alive_mutex));
	}
}
