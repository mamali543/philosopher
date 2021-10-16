/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:26:57 by mamali            #+#    #+#             */
/*   Updated: 2021/10/16 19:52:27 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_args(char **argv)
{
	if (ft_atoi(argv[1]) == 0)
		return (0);
	if (argv[5])
		if (ft_atoi(argv[5]) == 0)
			return (0);
	return (1);
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
