/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:17:54 by mamali            #+#    #+#             */
/*   Updated: 2021/09/26 17:42:35 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*ft_lstlastfork(t_fork *lst)
{
	t_fork *tmp = lst;
	if (!tmp)
		return (lst);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_philo	*ft_lstlast(t_philo *lst)
{
	t_philo *tmp = lst;
	if (!tmp)
		return (lst);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_back_fork(t_fork **head, t_fork *new_philo)
{
	new_philo->next = NULL;
	if (!head || !*head)
		*head = new_philo;
	else
		ft_lstlastfork(*head)->next = new_philo;
}

void	add_back(t_philo **head, t_philo *new_philo)
{
	new_philo->next = NULL;
	if (!head || !*head)
		*head = new_philo;
	else
		ft_lstlast(*head)->next = new_philo;
}

t_fork	*get_fork(t_data *data, int id)
{
	t_fork	*fork;

	fork = data->fork;
	while (fork)
	{
		if (fork->philo == id)
			return (fork);
		fork = fork->next;
	}
	return (NULL);
}
