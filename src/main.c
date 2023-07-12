/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:24:30 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/12 18:35:45 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isformatted(char **argv, int argc, t_philos *s)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		ft_printf("Usage: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat\n");
		return (0);
	}
	while (argv[i])
	{
		if (!ft_isnum(argv[i++]))
			return (ft_printf("%s not a valid number\n", argv[i - 1]), 0);
	}
	s->nphilo = ft_atoi(argv[1]);
	if (s->nphilo <= 0)
		return (ft_printf("Not enough philosophers\n"), 0);
	s->tdie = ft_atoi(argv[2]);
	if (s->tdie <= 0)
		return (ft_printf("Wrong time to die\n"), 0);
	s->teat = ft_atoi(argv[3]);
	if (s->teat <= 0)
		return (ft_printf("Wrong time to eat\n"), 0);
	s->tsleep = ft_atoi(argv[4]);
	if (s->tsleep <= 0)
		return (ft_printf("Wrong time to sleep\n"), 0);
	if (argv[5])
	{
		s->tmusteat = ft_atoi(argv[5]);
		if (s->tmusteat <= 0)
			return (ft_printf("Wrong time to each philo eats\n"), 0);
	}
	return (1);
}

void	ft_initstruct(t_philos *s)
{
	s->nphilo = 0;
	s->tdie = 0;
	s->teat = 0;
	s->tsleep = 0;
	s->tmusteat = 0;
}

void	*ft_runphilos()
{
	ft_printf("I am a philo\n");
	return (0);
}

int	ft_startphilos(t_philos *s)
{
	int	i;

	i = 0;
	s->philo = (pthread_t *)malloc((s->nphilo) * sizeof(pthread_t));
	while (i < s->nphilo)
	{
		if (pthread_create(&s->philo[i], NULL, &ft_runphilos, NULL) != 0)
			return (ft_printf("Failed to create a thread"), 0);
		i++;
	}
	i = 0;
	while (i < s->nphilo)
	{
		if (pthread_join(s->philo[i], NULL) != 0)
			return (ft_printf("Failed to join thread"), 0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philos	s;

	ft_initstruct(&s);
	if (!ft_isformatted(argv, argc, &s))
		return (1);
	if (!ft_startphilos(&s))
		return (1);
	return (0);
}
