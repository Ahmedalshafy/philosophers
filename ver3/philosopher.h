
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>

typedef struct s_data
{
    int				        philo_nbr;
    int				        meal_nbr;
    int                     is_dead;
    u_int64_t				time_to_die;
    u_int64_t				time_to_eat;
    u_int64_t				time_to_sleep;
    pthread_mutex_t         print;
    pthread_t               checks;
}					        t_data;

typedef struct s_philosopher
{
    int				    id;
    int                 fork;
    int*                next_fork;
    int                 eat_count;
    u_int64_t           last_meal;
    u_int64_t           start_time;
    pthread_t           th;
    pthread_mutex_t     fork_lock;
    pthread_mutex_t     *next_fork_lock;
    t_data              *data;
}					t_philosopher;

int   init_data(t_data *data, char **argv);
int   init_philosophers(t_data *data);
void  *philosopher(void *arg);
int   ft_atoi(char *str);
u_int64_t   get_time(void);
void  philo_state(t_philosopher *philo, char *state);
void  is_eating(t_philosopher *philo);
int  init_threads(t_philosopher *philosophers, t_data *data);
int ft_usleep(u_int64_t time);
u_int16_t time_stamp(u_int16_t start_time);
void  philo_eat(t_philosopher *philo);
void  philo_sleep(t_philosopher *philo);
void  philo_think(t_philosopher *philo);
int  init_philosophers_mutexes(t_philosopher *philosophers, t_data *data);
void  init_philosophers_data(t_philosopher *philosophers, t_data *data);
int  create_philosopher_thread(t_philosopher *philosophers, t_data *data);
void  destroy_philosophers_mutexes(t_philosopher *philosophers, t_data *data);
void  *philo_rotine(void *arg);
void *checks(void *arg);
int check_eat_time(t_philosopher *philo);
int check_die(t_philosopher *philo);
