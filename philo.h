#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_fork
{
	int				philo;
	int				new_philo;
	pthread_mutex_t	flock;
	struct s_fork	*next;
}				t_fork;

typedef struct s_philo
{
	int				id;
	int				statu;
	pthread_t		thread_id;
	int				eaten_meals;
	unsigned int	start_t_todie;
	int				fork;
	int				fork1;
	struct s_philo	*next;
}				t_philo;

typedef struct g_data
{
	int				nofphilo;
	unsigned int	t_to_sleep;
	unsigned int	t_to_die;
	unsigned int	t_to_eat;
	pthread_mutex_t	lock;
	int				required_meals;
	t_philo			*philo;
	t_fork			*fork;
}				t_data;

void			ft_putnbr_fd(int n, int fd);
t_fork			*get_fork(t_data *data, int id);
void			print(char *str, t_philo *philo, unsigned int i, int w);
unsigned int	get_time_mls(void);
void			sleep_thread(unsigned int limit, t_philo *philo);
void			check_if_philo_dead(t_philo *philo, t_data *data);
int				check_if_philo_readytoeat(t_data *data, t_philo *philo);
void			free_fork(t_data *data, t_philo *philo);
void			ft_init(char **argv, t_data *data);
t_fork			*forklist(t_data *data);
t_philo			*philolist(t_data *data);
void			add_back_fork(t_fork **head, t_fork *new_philo);
void			add_back(t_philo **head, t_philo *new_philo);
t_philo			*create_new_philo(int	i);
t_fork			*create_new_fork(int i);
void			printlist(t_philo *head);

#endif
