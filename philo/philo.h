/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:43:07 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/09/20 11:49:38 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <pthread.h>
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free
# include <string.h>   // memset
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // write, usleep

typedef struct s_philo	t_philo;
typedef struct s_tool
{
	long				fork_num;
	long long			ttd;
	long long			tte;
	long long			tts;
	long				eat_time;
	long				index;
	pthread_mutex_t		*mutexes;
	t_philo				*philos;
	int					philos_alive;
	pthread_mutex_t		alive_mutex;
	long long			start_time;
}						t_tool;

typedef struct s_philo
{
	long				id;
	long				eat_time;
	long long			state_time;
	pthread_t			thread;
	t_tool				*tool;
}						t_philo;

// main.c
void					*run_philosopher_loop(void *arg);
long long				get_current_time(void);

// initialization.c
void					initialize_tool(t_tool *tool, char **argv, int argc);
void					initialize_mutexes(t_tool *tool);
long					philo_atol(const char *str);
void					initialize_philos(t_philo **philos, int num,
							t_tool *tool);

// utils.c
void					put_message(char *message, long num, t_tool *tool);
long long				get_current_time(void);

// error.c
int						validate_input(int argc, char **argv);
int						check_valid_num(char *arg);

// monitor.c
void					check_all_philos(t_tool *tool);
int						track_meals(t_tool *tool, t_philo *philos,int i);
void					*monitor_routine(void *arg);
#endif