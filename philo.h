#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

typedef struct s_fork
{
	int				philo;
	int				new_philo;
	pthread_mutex_t flock;
	struct s_fork	*next;
}				t_fork;

typedef	struct	s_philo
{
	int		id;
	int		statu;
	pthread_t 		trd_id;
	int				t_eat;
	unsigned int	t_stop_eat;
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
	pthread_mutex_t lock;
	int				t_must_eat;
	t_philo			*philo;
	t_fork			*fork;
}				t_data;

void			ft_putnbr_fd(int n, int fd);
void	ft_philo(t_data *data);
void	ft_print(char *str, t_philo *philo, unsigned int i, int w);
unsigned int	get_time_mls(void);
#endif
