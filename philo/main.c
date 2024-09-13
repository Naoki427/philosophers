/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:24:14 by yoshiminaok       #+#    #+#             */
/*   Updated: 2024/09/13 23:41:44 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void *run_philosopher_loop(void *arg);
long long get_current_time();
void *monitor_routine(void *arg);

int main(int argc,char **argv)
{
    t_tool tool;
    t_philo *philos;
    pthread_t monitor_thread;
    
    if (argc != 5 && argc != 6)
        return (0);
    initialize_tool(&tool,argv,argc);
    initialize_mutexes(&tool);
    initialize_philos(&philos,tool.fork_num,&tool);
    tool.philos = philos; 
    while(tool.index < tool.fork_num)
    {
        philos[tool.index].id = tool.index;
        pthread_create(&(philos[tool.index].thread),NULL,run_philosopher_loop,&(philos[tool.index]));
        tool.index++; 
    }
    pthread_create(&monitor_thread,NULL,monitor_routine,&tool);
    tool.index = 0;
    while(tool.index < tool.fork_num)
    {
        pthread_join(philos[tool.index].thread,NULL);
        tool.index++; 
    }
    pthread_join(monitor_thread,NULL);
    return (0);
}

void do_sycle(t_tool *tool,t_philo *philo)
{
    int left_fork;

    if(philo->id == 0)
        left_fork = tool->fork_num - 1;
    else
        left_fork = philo->id - 1;
    pthread_mutex_lock(&(tool->mutexes[philo->id]));
    put_message("%lld %ld has taken a fork\n",philo->id + 1,tool);
    pthread_mutex_lock(&(tool->mutexes[left_fork]));
    put_message("%lld %ld has taken a fork\n",philo->id + 1,tool);
    put_message("%lld %ld is eating\n",philo->id + 1,tool);
    philo->state_time = get_current_time();
    philo->eat_time++;
    usleep(1000*tool->tte);
    pthread_mutex_unlock(&(tool->mutexes[left_fork]));
    pthread_mutex_unlock(&(tool->mutexes[philo->id]));
    put_message("%lld %ld is sleeping\n",philo->id + 1,tool);
    usleep(1000*tool->tts);
    put_message("%lld %ld is thinking\n",philo->id + 1,tool);
}

void *run_philosopher_loop(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    if (philo->id % 2 == 1)
        usleep(200);
    while(philo->tool->philos_alive)
    {
        do_sycle(philo->tool,philo);
        // break;
    }
    return (NULL);
}

long long get_current_time() 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);
}

void *monitor_routine(void *arg)
{
    t_tool *tool;
    long i;

    tool = (t_tool *)arg;
    i = 0;
    while (tool->philos_alive)
    {
        while(i < tool->fork_num)
        {
            if (get_current_time() - tool->philos[i].state_time >= tool->ttd)
            {
                 put_message("%lld %ld died\n",i+1,tool);
                 tool->philos_alive = 0;
                 break;
            }
        }
        usleep(10000);
        
    }
    return (NULL);
}

// how to use timestamp

// int main()
// {
//     struct timeval tv;
//     gettimeofday(&tv, NULL);
//     long long milliseconds = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
//     put_message("%lld\n",milliseconds);
//     return 0;
// }