/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:40:33 by jperras           #+#    #+#             */
/*   Updated: 2022/04/02 15:17:06 by jperras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <Philosophers.h>

void	*routine(void *void_args)
{
	int				i;
	t_philosophers	*philo;

	philo = (t_philosophers *) void_args;
	i = 1;
	gettimeofday(&philo->life, NULL);
	ft_routine_death(philo);
	philo->number_of_eat = i;
	while (philo->number_of_eat
		!= philo->rules->number_of_times_each_philosopher_must_eat
		&& philo->rules->death != 1)
	{
		philo->number_of_eat = i;
		if (philo->rules->death != 1)
			ft_eat(philo);
		if (philo->rules->death != 1)
			ft_sleep(philo);
		if (philo->rules->death != 1)
			ft_think(philo);
		i++;
	}
	if (philo->rules->death != 1 && philo->number_of_eat
		== philo->rules->number_of_times_each_philosopher_must_eat)
		philo->rules->win = 1;
	return (0);
}

static void	ft_init(t_rules *rules, char **argv, int argc)
{
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		rules->number_of_times_each_philosopher_must_eat = -1;
	ft_init_mutex(rules);
	rules->death = 0;
	rules->win = 0;
}

int	main(int argc, char **argv)
{
	t_rules			rules;
	t_philosophers	*philo;
	int				i;
	int				flag;

	philo = NULL;
	flag = ft_check(argc, argv);
	if (flag == 1 || argc > 6 || argc < 5)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	else if (flag == 2)
		return (0);
	ft_init(&rules, argv, argc);
	philo = ft_init_philo(&rules, philo);
	i = 0;
	while (i < rules.nb_philo)
	{
		philo[i].rules = &rules;
		i++;
	}
	ft_init_pthread(philo);
	return (0);
}
