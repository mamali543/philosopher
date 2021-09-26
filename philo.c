#include "philo.h"

struct g_data	data;

void	ft_putchar_fd(char c, int i)
{
	write(i, &c, 1);
}

unsigned int	get_time_mls(void)
{
	struct timeval	time;
	unsigned int	i;

	gettimeofday(&time, NULL);
	i = (unsigned int)time.tv_sec;
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void			ft_putnbr_fd(int n, int fd)
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
	if (s[0] != 'd')
		pthread_mutex_unlock(&data.lock);
}


void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		ft_putchar_fd(str[i++], 1);
}

void	log_error(char *str)
{
	ft_putstr(str);
	ft_putchar_fd('\n', 1);
	exit(1);
}

void	ft_init(char **argv, t_data *data)
{
	data->fork = NULL;
	data->philo =  NULL;
	data->nofphilo = atoi(argv[1]);
	if (data->nofphilo < 1)
		print("invalid arguments\n", NULL, 0, 3);
	data->t_to_die = atoi(argv[2]);
	data->t_to_eat = atoi(argv[3]);
	data->t_to_sleep = atoi(argv[4]);
	if (argv[5])
	data->t_must_eat = atoi(argv[5]);
	else
		data->t_must_eat = -1;
}

void	printlist(t_philo *head)
{
	t_philo	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		printf("%d\n", tmp->id);
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



t_philo		*create_new_philo(int	i)
{
	t_philo *philo;

	philo = (t_philo *)malloc(sizeof(*philo));
	philo->id = i;
	philo->statu = 0;
	philo->t_eat = 0;
	philo->t_stop_eat = get_time_mls();
	philo->next = NULL;
	return (philo);
}

t_fork		*create_new_fork(int i)
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

t_fork	*forklist(t_data *data)
{
	t_fork *fork;
	int		i;

	i = 1;
	fork = NULL;
	while (i <= data->nofphilo)
		add_back_fork(&(fork), create_new_fork(i++));
	if (pthread_mutex_init(&fork->flock, NULL) != 0)
		print("\n mutex init failed\n", NULL, 0, 2);	
	return (fork);
}

t_philo	*philolist(t_data *data)
{
	t_philo	*philo;

	int		i;

	i = 1;
	philo = NULL;
	while (i <= data->nofphilo)
		add_back(&(philo), create_new_philo(i++));
	return (philo);
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

	// exit(1);
	fork = get_fork(data, philo->id);
	// printf(" %d philo-id = %d %d <<%d>>\n", get_time_mls(), philo->id, fork->new_philo, philo->statu);
	// exit(1);
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
	{
		usleep(50);
		// philo check death only if he doesn't eat
		 //check_if_philo_dead(philo, &data);
	}
	
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
		if (philo->id % 2 == 1 && data->nofphilo >= philo->id + 1)
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
