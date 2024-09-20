/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:25:53 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/09/19 13:44:04 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
}
