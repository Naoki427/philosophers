#include <string.h>      // memset
#include <stdio.h>       // printf
#include <stdlib.h>      // malloc, free
#include <unistd.h>      // write, usleep
#include <sys/time.h>    // gettimeofday
#include <pthread.h>     // pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
#include <limits.h>
typedef struct s_tool {
    long fork_num;
    long ttd;
    long tte;
    long tts;
    long eat_time;
    struct timeval tv;
    int is_dead;
    pthread_mutex_t mutex;
    int *forks;
    long    index;
} t_tool;

typedef struct s_philo {
    int state;
    long eat_time;
    long long state_time;
    pthread_t thread;
} t_philo;

typedef enum e_state {
    TAKING_ZERO = 0,
    TAKING_ONE = 1,
    TAKING_TWO = 2,
    EATING = 3,
    SLEEPING = 4,
    DIED = 5
} t_state;

//main.c

//initialization.c
void    initialize_tool(t_tool *tool,char **argv,int argc);
long	philo_atol(const char *str);
void initialize_philos(t_philo **philos,int num);