/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshiminaoki <yoshiminaoki@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:24:14 by yoshiminaok       #+#    #+#             */
/*   Updated: 2024/09/13 20:24:27 by yoshiminaok      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void *run_philosopher_loop(void *arg);
long long get_current_time();

int main(int argc,char **argv)
{
    t_tool tool;
    t_philo *philos;
    
    initialize_tool(&tool,argv,argc);
    initialize_philos(&philos,tool.fork_num,&tool);
    while(tool.index < tool.fork_num)
    {
        philos[tool.index].id = tool.index;
        pthread_create(&(philos[tool.index].thread),NULL,run_philosopher_loop,&(philos[tool.index]));
        pthread_detach(philos[tool.index].thread);
        tool.index++; 
    }
    return (0);
}

void complete_eating(t_tool *tool,t_philo *philo)
{
    int left_fork;

    if(philo->id == 0)
        left_fork = tool->fork_num - 1;
    else
        left_fork = philo->id - 1;
    pthread_mutex_lock(&(tool->mutexes[philo->id]));
    pthread_mutex_lock(&(tool->mutexes[left_fork]));
    printf("%lld %ld is eating\n",get_current_time(),philo->id + 1);
    philo->state_time = get_current_time();
    usleep(1000*tool->tte);
    pthread_mutex_unlock(&(tool->mutexes[left_fork]));
    pthread_mutex_unlock(&(tool->mutexes[philo->id]));
}

void *run_philosopher_loop(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    if (philo->id % 2 == 1)
        usleep(200);
    while(1)
    {
        complete_eating(philo->tool,philo);
    }
    return (NULL);
}

long long get_current_time() 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);
}

// how to use timestamp

// int main()
// {
//     struct timeval tv;
//     gettimeofday(&tv, NULL);
//     long long milliseconds = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
//     printf("%lld\n",milliseconds);
//     return 0;
// }