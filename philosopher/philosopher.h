
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>

typedef struct s_data
{
    int				philo_nbr;
    int                dead_flag;
    u_int64_t				time_to_die;
    u_int64_t				time_to_eat;
    u_int64_t				time_to_sleep;
    pthread_mutex_t        print;
    pthread_mutex_t        dead_status;
    pthread_mutex_t        meal_count_lock;
    pthread_t               checks;
    int				        meal_nbr;
}					t_data;

typedef struct s_philosopher
{
    int				    id;
    int                 fork;
    int*                next_fork;
    int                 *dead;
    int                 meal_count;
    u_int64_t           last_meal;
    u_int64_t           start_time;
    t_data              *data;
    pthread_t           th;
    pthread_mutex_t     fork_lock;
    pthread_mutex_t     *next_fork_lock;
    pthread_mutex_t     *print;
    pthread_mutex_t	 	*dead_status;
    pthread_mutex_t     *meal_count_lock;
}					t_philosopher;




int   init_data(t_data *data, char **argv);
int   init_philosophers(t_data *data);
void  *philosopher(void *arg);
int   ft_atoi(char *str);
u_int64_t   get_time(void);
void  philo_state(t_philosopher *philo, char *state);
void  is_eating(t_philosopher *philo);
void  *check_die(void *arg);
int  init_threads(t_philosopher *philosophers, t_data *data);
int ft_usleep(u_int64_t time);
u_int16_t time_stamp(u_int16_t start_time);