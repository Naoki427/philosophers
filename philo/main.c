/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshiminaoki <yoshiminaoki@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:24:14 by yoshiminaok       #+#    #+#             */
/*   Updated: 2024/09/13 18:03:35 by yoshiminaok      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void run_philosopher_loop(t_tool *tool,t_philo **philos);

int main(int argc,char **argv)
{
    t_tool tool;
    t_philo *philos;
    
    initialize_tool(&tool,argv,argc);
    initialize_philos(&philos,tool.fork_num);
    while(tool.index < tool.fork_num)
    {
        pthread_create(&(philos[tool.index].thread),NULL,run_philosopher_loop,&tool);  
    }
}

void run_philosopher_loop(t_tool *tool,t_philo **philos)
{
     
    if (tool->index % 2 == 1)
        usleep(200);
    while(1)
    {
        
    }
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