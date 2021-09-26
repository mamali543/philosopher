/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:12:35 by mamali            #+#    #+#             */
/*   Updated: 2021/09/26 16:13:42 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_time_mls(void)
{
	struct timeval	time;
	unsigned int	i;

	gettimeofday(&time, NULL);
	i = (unsigned int)time.tv_sec;
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	free_fork(t_data *data, t_philo *philo)
{
	t_fork	*fork;
	t_fork	*fork1;

	fork = get_fork(data, philo->id);
	if (fork->new_philo == -1)
		return ;
	if (philo->id < data->nofphilo)
		fork1 = get_fork(data, philo->id + 1);
	else
		fork1 = get_fork(data, 1);
	if (fork->new_philo != -1 && fork1->new_philo != -1)
	{
		philo->fork = 0;
		philo->fork1 = 0;
		fork->new_philo = -1;
		fork1->new_philo = -1;
		return ;
	}
}

int		check_if_philo_readytoeat(t_data *data, t_philo *philo)
{
	t_fork	*fork;
	t_fork	*fork1;

	fork = get_fork(data, philo->id);
	pthread_mutex_lock(&fork->flock);
	if (fork->new_philo == -1)
	{
		philo->fork = 1;
		print("has taken a fork", philo, get_time_mls(), 1);
		fork->new_philo = philo->id;
	}
	pthread_mutex_unlock(&fork->flock);
	if (philo->id == data->nofphilo)
		fork1 = get_fork(data, 1);
	else
		fork1 = get_fork(data, philo->id + 1);
	pthread_mutex_lock(&fork1->flock);
	if (fork1->new_philo == -1)
	{
		print("has taken a fork", philo, get_time_mls(), 1);
		fork1->new_philo = philo->id;
		philo->fork1 = 1;
	}
	pthread_mutex_unlock(&fork1->flock);
	if (data->nofphilo == 1)
		return (0);
	return (philo->fork1 && philo->fork);
}

void	check_if_philo_dead(t_philo *philo, t_data *data)
{
	if (get_time_mls() - philo->t_stop_eat >= data->t_to_die)
	{
		print("died", philo, get_time_mls(), 1);
		exit(1);
	}
}

void	sleep_thread(unsigned int limit, t_philo *philo)
{
	unsigned int	i;

	i = get_time_mls();
	philo = NULL;
	while (get_time_mls() - i < limit)
		usleep(50);
	// philo check death only if he doesn't eat
	//check_if_philo_dead(philo, &data);
}