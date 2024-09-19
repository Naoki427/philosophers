/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:24:14 by yoshiminaok       #+#    #+#             */
/*   Updated: 2024/09/19 13:41:14 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*run_philosopher_loop(void *arg);
long long	get_current_time(void);
void		*monitor_routine(void *arg);
void		cleanup_all(t_tool *tool, t_philo *philos);
void		create_threads(t_tool *tool, t_philo *philos);

int	main(int argc, char **argv)
{
	t_tool		tool;
	t_philo		*philos;
	pthread_t	monitor_thread;

	if (validate_input(argc, argv))
		return (1);
	initialize_tool(&tool, argv, argc);
	initialize_philos(&philos, tool.fork_num, &tool);
	tool.philos = philos;
	create_threads(&tool, philos);
	pthread_create(&monitor_thread, NULL, monitor_routine, &tool);
	while (tool.index < tool.fork_num)
	{
		if (tool.fork_num == 1)
			pthread_detach(philos[tool.index].thread);
		else
			pthread_join(philos[tool.index].thread, NULL);
		tool.index++;
	}
	pthread_join(monitor_thread, NULL);
	cleanup_all(&tool, philos);
	return (0);
}

void	do_sycle(t_tool *tool, t_philo *philo)
{
	int	left_fork;

	if (philo->id == 0)
		left_fork = tool->fork_num - 1;
	else
		left_fork = philo->id - 1;
	pthread_mutex_lock(&(tool->mutexes[philo->id]));
	put_message("%lld %ld has taken a fork\n", philo->id + 1, tool);
	pthread_mutex_lock(&(tool->mutexes[left_fork]));
	put_message("%lld %ld has taken a fork\n", philo->id + 1, tool);
	put_message("%lld %ld is eating\n", philo->id + 1, tool);
	philo->state_time = get_current_time();
	philo->eat_time++;
	usleep(1000 * tool->tte);
	pthread_mutex_unlock(&(tool->mutexes[left_fork]));
	pthread_mutex_unlock(&(tool->mutexes[philo->id]));
	put_message("%lld %ld is sleeping\n", philo->id + 1, tool);
	usleep(1000 * tool->tts);
	put_message("%lld %ld is thinking\n", philo->id + 1, tool);
}

void	*run_philosopher_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(300);
	while (philo->tool->philos_alive)
	{
		do_sycle(philo->tool, philo);
	}
	return (NULL);
}

void	create_threads(t_tool *tool, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < tool->fork_num)
	{
		philos[i].id = i;
		pthread_create(&(philos[i].thread), NULL, run_philosopher_loop,
			&(philos[i]));
		i++;
	}
}

void	cleanup_all(t_tool *tool, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < tool->fork_num)
	{
		pthread_mutex_destroy(&(tool->mutexes[i]));
		i++;
	}
	free(tool->mutexes);
	free(philos);
	pthread_mutex_destroy(&(tool->alive_mutex));
}
