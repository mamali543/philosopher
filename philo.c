#include "philo.h"

struct g_data	data;

void	print(char *s, t_philo *philo, unsigned int a, int b)
{
	if (b != 3)
		pthread_mutex_lock(&data.lock);
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
	// if (s[0] != 'd')
	pthread_mutex_unlock(&data.lock);
}

t_philo	*get_philo(t_data *data, int philo_id)
{
	t_philo *philo;

	philo = data->philo;
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
	check_if_philo_dead(philo, data);
	if (philo->statu == 0 || philo->statu == 3)
		philo->statu = check_if_philo_readytoeat(data, philo);
	else if (philo->statu == 1)
	{
		free_fork(data, philo);
		philo->t_eat++;
		philo->statu = 2;
	}
	else if (philo->statu == 2)
		philo->statu = 3;
}

void	*ft_routine(void *i)
{
	int		*id;
	t_philo	*philo;

	id = (int *)i;
	philo = get_philo(&data, *id);
	while (1)
	{
		if (philo->statu == 1)
		{
			print("is eating", philo, get_time_mls(), 1);
			philo->t_stop_eat = get_time_mls();
			sleep_thread(data.t_to_eat, philo);
		}
		else if (philo->statu == 2)
		{
			print("is sleeping", philo, get_time_mls(), 1);
			sleep_thread(data.t_to_sleep, philo);
		}
		else if (philo->statu == 3)
			print("is thinking", philo, get_time_mls(), 1);
		check_philo_statu(philo, &data);
	}
}

void	ft_philo(t_data *data)
{
	t_philo	*philo;
	t_fork	*fork;

	philo = data->philo;
	while (philo)
	{
		if (philo->id % 2 == 1 && data->nofphilo != philo->id)
		{
			fork = get_fork(data, philo->id);
			fork->new_philo = philo->id;
			fork = get_fork(data, philo->id + 1);
			fork->new_philo = philo->id;
			philo->statu = 1;
			print("has taken a fork", philo, get_time_mls(), 1);
			print("has taken a fork", philo, get_time_mls(), 1);
		}
		else
			philo->statu = 0;
		if (pthread_create(&philo->trd_id, NULL, &ft_routine, &philo->id) != 0)
			print("can't create thread", philo, 0, 2);
		philo = philo->next;
	}
	while (1);
}

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (-1);
	ft_init(argv, &data);
	data.philo = philolist(&data);
	data.fork = forklist(&data);
	if (pthread_mutex_init(&data.lock, NULL) != 0)
		print("\n mutex init failed\n", NULL, 0, 2);	
	ft_philo(&data);
	return 0;
}
