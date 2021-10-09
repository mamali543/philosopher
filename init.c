/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:20:42 by mamali            #+#    #+#             */
/*   Updated: 2021/10/09 21:25:01 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(char **argv, t_data *data)
{
	data->fork = NULL;
	data->nofphilo = atoi(argv[1]);
	if (data->nofphilo < 1)
		print("invalid arguments\n", NULL, 0, 3);
	data->t_to_die = atoi(argv[2]);
	data->t_to_eat = atoi(argv[3]);
	data->t_to_sleep = atoi(argv[4]);
	if (argv[5])
		data->required_meals = atoi(argv[5]);
	else
		data->required_meals = -1;
}

t_fork	*forklist(t_data *data)
{
	t_fork	*fork;
	int		i;

	i = 1;
	fork = NULL;
	while (i <= data->nofphilo)
		add_back_fork(&(fork), create_new_fork(i++));
	return (fork);
}

t_philo	*philolist(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 1;
	philo = NULL;
	while (i <= data->nofphilo)
		add_back(&(philo), create_new_philo(i++, data));
	return (philo);
}

void	printlist(t_philo *head)
{
	t_philo	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		printf("%d\n", tmp->eaten_meals);
		tmp = tmp->next;
	}
}

void	printlistf(t_fork *head)
{
	t_fork	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		printf("%d\n", tmp->philo);
		tmp = tmp->next;
	}
}

t_philo	*create_new_philo(int i , t_data *data)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(*philo));
	philo->id = i;
	philo->statu = 0;
	philo->eaten_meals = 0;
	philo->start_t_todie = get_time_mls();
	philo->data = data;
	philo->fork = 0;
	philo->fork1 = 0;
	philo->next = NULL;
	return (philo);
}

t_fork	*create_new_fork(int i)
{
	t_fork	*fork;

	fork = (t_fork *)malloc(sizeof(*fork));
	fork->philo = i;
	fork->new_philo = -1;
	fork->next = NULL;
	if (pthread_mutex_init(&fork->flock, NULL) != 0)
		print("\n mutex init failed\n", NULL, 0, 2);
	return (fork);
}
