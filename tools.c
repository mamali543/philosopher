/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:47:23 by mamali            #+#    #+#             */
/*   Updated: 2021/10/11 18:25:56 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philo **node)
{
	t_philo	*tmp;

	while (*node)
	{
		tmp = *node;
		*node = (*node)->next;
		free(tmp);
	}
}

void	free_f(t_fork **node)
{
	t_fork	*tmp;

	while (*node)
	{
		tmp = *node;
		*node = (*node)->next;
		free(tmp);
	}
}

void	free_function(t_fork **fork, t_data *data, t_philo **philo)
{
	free_f(fork);
	free(data);
	free_philo(philo);
}

int	handle_error(int ac, char **argv)
{
	int		i;
	int		j;

	if (ac == 5 || ac == 6)
	{
		i = 1;
		while (argv[i])
		{
			j = 0;
			while (argv[i][j])
			{
				if (ft_isdigit(argv[i][j]) == 0)
					return (0);
				j++;
			}
			i++;
		}
	}
	else
		return (0);
	return (1);
}
