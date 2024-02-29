
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_data
{
    int				philo_nbr;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				meal_nbr;
}					t_data;

typedef struct s_philosopher
{
    int				    id;
    t_data              *data;
    pthread_t           th;
    pthread_mutex_t     left_fork;
    pthread_mutex_t     right_fork;
}					t_philosopher;




int   init_data(t_data *data, char **argv);
int   init_philosophers(t_data *data);
void  *philosopher(void *arg);
int   ft_atoi(char *str);
long   get_time(void);