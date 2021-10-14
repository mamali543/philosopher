/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:26:57 by mamali            #+#    #+#             */
/*   Updated: 2021/10/11 16:47:32 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar_fd(char c, int i)
{
	write(i, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	i;

	i = n;
	if (i < 0)
	{
		i = -i;
		ft_putchar_fd(45, fd);
	}
	if (i > 9)
	{
		ft_putnbr_fd(i / 10, fd);
		ft_putchar_fd(i % 10 + 48, fd);
	}
	if (i <= 9 && i >= 0)
	{
		ft_putchar_fd(i + 48, fd);
	}
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
