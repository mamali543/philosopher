/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:00:51 by mamali            #+#    #+#             */
/*   Updated: 2021/10/16 21:25:55 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_data
{
	int				nofphilo;
	unsigned int	t_to_sleep;
	unsigned int	t_to_die;
	unsigned int	t_to_eat;
	pthread_mutex_t	lock;
	int				required_meals;
	t_fork			*fork;
	unsigned long	start;
	pthread_mutex_t	help;
	int				o;
}				t_data;

typedef struct s_philo
{
	int				id;
	int				statu;
	pthread_t		thread_id;
	int				eaten_meals;
	unsigned long	start_t_todie;
	int				fork;
	int				fork1;
	t_data			*data;
	struct s_philo	*next;
}				t_philo;

t_fork			*get_fork(t_data *data, int id);
void			print(char *str, t_philo *philo, unsigned long i, int w);
unsigned long	get_time_mls(void);
void			sleep_thread(unsigned int limit, t_philo *philo);
void			check_if_philo_dead(t_philo *philo, t_data *data);
int				is_ready(t_data *data, t_philo *philo, t_fork *fork, \
				 t_fork *fork1);
void			free_fork(t_data *data, t_philo *philo);
void			ft_init(char **argv, t_data *data);
t_fork			*forklist(t_data *data);
t_philo			*philolist(t_data *data);
void			add_back_fork(t_fork **head, t_fork *new_philo);
void			add_back(t_philo **head, t_philo *new_philo);
t_philo			*create_new_philo(int	i, t_data *data);
t_fork			*create_new_fork(int i);
void			printlist(t_philo *head);
void			printlistf(t_fork *head);
void			free_philo(t_philo **node);
void			free_f(t_fork **node);
void			free_function(t_fork **fork, t_data *data, t_philo **philo);
int				handle_error(int ac, char **argv);
long long		ft_atoi(const char *str);
int				ft_isdigit(int c);
void			log_error(char *msg);
int				handle_args(char **argv);

#endif