/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:24:03 by jperras           #+#    #+#             */
/*   Updated: 2022/04/02 14:53:10 by jperras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Philosophers.h"

void	*ft_routine_death(t_philosophers *philo)
{
	pthread_t	thread2;
	
	if (pthread_create(&thread2, NULL, &ft_dead, philo) != 0)
		return (0);
	return (0);
}
