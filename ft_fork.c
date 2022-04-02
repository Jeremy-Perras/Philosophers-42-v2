/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:58:25 by jperras           #+#    #+#             */
/*   Updated: 2022/04/02 14:52:13 by jperras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Philosophers.h"

static void	*ft_fork_next(t_philosophers *philo)
{
	printf("%Lf %d has taken a fork\n",
		ft_time(philo->begin, philo->start), philo->id);
	printf("%Lf %d is eating\n", ft_time(philo->begin, philo->start), philo->id);
	gettimeofday(&philo->life, NULL);
	gettimeofday(&philo->end, NULL);
	while (ft_time(philo->end, philo->begin) < philo->rules->time_to_eat)
		gettimeofday(&philo->end, NULL);
	pthread_mutex_unlock(&(philo->rules->mutex[philo->rightid]));
	pthread_mutex_unlock(&(philo->rules->mutex[philo->id]));
	return (0);
}

void	*ft_fork(t_philosophers *philo)
{
	pthread_mutex_lock(&(philo->rules->mutex[philo->id]));
	gettimeofday(&philo->begin, NULL);
	if (philo->rules->death == 1)
	{
		pthread_mutex_unlock(&(philo->rules->mutex[philo->id]));
		return (0);
	}
	printf("%Lf %d has taken a fork\n",
		ft_time(philo->begin, philo->start), philo->id);
	pthread_mutex_lock(&(philo->rules->mutex[philo->rightid]));
	gettimeofday(&philo->begin, NULL);
	if (philo->rules->death == 1)
	{
		pthread_mutex_unlock(&(philo->rules->mutex[philo->rightid]));
		pthread_mutex_unlock(&(philo->rules->mutex[philo->id]));
		return (0);
	}
	ft_fork_next(philo);
	return (0);
}

static void	*ft_right_fork_next(t_philosophers *philo)
{	
	printf("%Lf %d has taken a fork\n", ft_time(philo->begin, philo->start),
		philo->id);
	printf("%Lf %d is eating\n", ft_time(philo->begin, philo->start),
		philo->id);
	gettimeofday(&philo->life, NULL);
	gettimeofday(&philo->end, NULL);
	while (ft_time(philo->end, philo->begin) < philo->rules->time_to_eat)
		gettimeofday(&philo->end, NULL);
	pthread_mutex_unlock(&(philo->rules->mutex[philo->id]));
	pthread_mutex_unlock(&(philo->rules->mutex[philo->rightid]));
	return (0);
}

void	*ft_right_fork(t_philosophers *philo)
{
	pthread_mutex_lock(&(philo->rules->mutex[philo->rightid]));
	gettimeofday(&philo->begin, NULL);
	if (philo->rules->death == 1)
	{
		pthread_mutex_unlock(&(philo->rules->mutex[philo->rightid]));
		return (0);
	}
	printf("%Lf %d has taken a fork\n", ft_time(philo->begin, philo->start),
		philo->id);
	pthread_mutex_lock(&(philo->rules->mutex[philo->id]));
	gettimeofday(&philo->begin, NULL);
	if (philo->rules->death == 1)
	{
		pthread_mutex_unlock(&(philo->rules->mutex[philo->id]));
		pthread_mutex_unlock(&(philo->rules->mutex[philo->rightid]));
		return (0);
	}
	ft_right_fork_next(philo);
	return (0);
}

void	ft_destroy(t_philosophers *philo, pthread_t *thread)
{
	int	i;
	int	j;

	i = 0;
	j = philo[0].rules->nb_philo;
	while (i < j)
	{
		pthread_join(thread[i], NULL);
		pthread_mutex_destroy(&philo[i].rules->mutex[i]);
		i++;
	}
	free(philo->rules->mutex);
	free(philo);
	free(thread);
}
