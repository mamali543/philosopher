/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 20:55:50 by macbookpro        #+#    #+#             */
/*   Updated: 2021/10/09 21:28:11 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(char *s, t_philo *philo, unsigned int a, int b)
{
	if (b != 3)
		pthread_mutex_lock(&philo->data->lock);
	if (b != 2 && b != 3)
	{
		ft_putnbr_fd(a, 1);
		write(1, " ", 1);
		ft_putnbr_fd((unsigned int)philo->id, 1);
		write(1, " ", 1);
	}
	write(1, s, strlen(s));
	write(1, "\n", 1);
	if (b == 3 || b == 2)
		exit(15);
	if (s[0] != 'd')
		pthread_mutex_unlock(&philo->data->lock);
}

t_philo	*get_philo(t_philo *philos, int philo_id)
{
	t_philo	*philo;

	philo = philos;
	while (philo)
	{
		if (philo->id == philo_id)
			return (philo);
		philo = philo->next;
	}
	return (NULL);
}

void	check_philo_statu(t_philo *philo, t_data *data)
{
	t_fork	*fork;
	t_fork	*fork1;

	check_if_philo_dead(philo, data);
	if (philo->statu == 0 || philo->statu == 3)
		philo->statu = check_if_philo_readytoeat(data, philo, fork, fork1);
	else if (philo->statu == 1)
	{
		free_fork(data, philo);
		philo->eaten_meals++;
		philo->statu = 2;
	}
	else if (philo->statu == 2)
		philo->statu = 3;
}

void	*ft_routine(void *i)
{
	int		id;
	t_philo	*philo;

	philo = (t_philo *)i;
	id = philo->id;
	while (1)
	{
		if (philo->statu == 1)
		{
			print("is eating", philo, get_time_mls(), 1);
			philo->start_t_todie = get_time_mls();
			sleep_thread(philo->data->t_to_eat, philo);
		}
		else if (philo->statu == 2)
		{
			print("is sleeping", philo, get_time_mls(), 1);
			sleep_thread(philo->data->t_to_sleep, philo);
		}
		else if (philo->statu == 3)
			print("is thinking", philo, get_time_mls(), 1);
		check_philo_statu(philo, philo->data);
	}
}

void	ft_philo(t_philo *philos)
{
	t_philo	*philo;
	t_fork	*fork;

	philo = philos;
	while (philo)
	{
		if (philo->id % 2 == 1 && philos->data->nofphilo != philo->id)
		{
			fork = get_fork(philos->data, philo->id);
			fork->new_philo = philo->id;
			fork = get_fork(philos->data, philo->id + 1);
			fork->new_philo = philo->id;
			philo->statu = 1;
			print("has taken a fork", philo, get_time_mls(), 1);
			print("has taken a fork", philo, get_time_mls(), 1);
		}
		else
			philo->statu = 0;
		if (pthread_create(&philo->thread_id, NULL, &ft_routine, philo) != 0)
			print("can't create thread", philo, 0, 2);
		philo = philo->next;
	}
	while (1);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_data		*data;
	t_fork		*fork;

	if (argc != 5 && argc != 6)
		return (-1);
	philo = malloc(sizeof(t_philo));
	data = malloc(sizeof(t_data));
	ft_init(argv, data);
	data->fork = forklist(data);
	philo = philolist(data);
	if (pthread_mutex_init(&philo->data->lock, NULL) != 0)
		print("\n mutex init failed\n", NULL, 0, 2);
	ft_philo(philo);
	return (0);
}
