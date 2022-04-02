/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:15:34 by jperras           #+#    #+#             */
/*   Updated: 2022/04/02 14:32:50 by jperras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <Philosophers.h>

void	ft_init_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	rules->mutex = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	while (i < rules->nb_philo)
	{
		pthread_mutex_init(&rules->mutex[i], NULL);
		i++;
	}
}

void	*ft_init_pthread(t_philosophers *philo)
{
	pthread_t	*thread;
	int			i;

	i = 0;
	thread = malloc(sizeof(pthread_t) * philo[0].rules->nb_philo);
	while (i < philo[0].rules->nb_philo)
	{
		usleep(50);
		gettimeofday(&philo[i].start, NULL);
		if (pthread_create(&thread[i], NULL, &routine, &(philo[i])) != 0)
			return (0);
		i++;
	}
	i = 0;
	//ft_dead(philo);
	ft_destroy(philo, thread);
	return (0);
}

t_philosophers	*ft_init_philo(t_rules *rules, t_philosophers *philo)
{
	int				i;

	i = 0;
	philo = malloc(sizeof(t_philosophers) * rules->nb_philo);
	while (i < rules->nb_philo)
	{
		if (i == 0)
		{
			philo[i].rightid = rules->nb_philo - 1;
			philo[i].leftid = i + 1;
		}
		else if (i == rules->nb_philo - 1)
		{
			philo[i].leftid = 0;
			philo[i].rightid = i - 1;
		}
		else
		{
			philo[i].leftid = i + 1;
			philo[i].rightid = i - 1;
		}
		philo[i].id = i;
		i++;
	}
	return (philo);
}

static int	ft_wait(char **argv)
{
	int				flag;
	struct timeval	begin;
	struct timeval	end;
	double			i;

	gettimeofday(&begin, NULL);
	gettimeofday(&end, NULL);
	i = ft_atoi(argv[2]);
	while (ft_time(end, begin) <= i)
		gettimeofday(&end, NULL);
	printf("%Lf %d died", ft_time(end, begin), 1);
	flag = 2;
	return (flag);
}

int	ft_check(int argc, char **argv)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	j = 0;
	flag = 0;
	if	(argc > 6 || argc < 5)
		flag = 1;
	while (i < argc && !flag)
	{
		while (argv[i][j] != '\0' && !flag)
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				flag = 1;
			j++;
		}
		j = 0;
		i++;
	}
	if (!flag && ft_atoi(argv[1]) == 1)
		flag = ft_wait(argv);
	if (!flag && ft_atoi(argv[1]) < 1)
		flag = 1;
	return (flag);
}
