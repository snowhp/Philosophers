/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:08:47 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/19 14:52:39 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_setargs(char **argv, t_philos *s)
{
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

int	ft_isformatted(char **argv, int argc, t_philos *s)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		ft_printf("Usage: number_of_philosophers time_to_die time_to_eat \
			time_to_sleep [number_of_times_each_philosopher_must_eat\n");
		return (0);
	}
	while (argv[i])
	{
		if (!ft_isnum(argv[i++]))
			return (ft_printf("%s not a valid number\n", argv[i - 1]), 0);
	}
	return (ft_setargs(argv, s));
}

void	ft_createpthreads(t_philos *s, t_philostats	*philo)
{
	int	i;

	i = 0;
	while (i < s->nphilo)
	{
		if (i % 2 == 0)
			pthread_create(&s->id[i], NULL, &ft_runphilos, (void *)&philo[i]);
		i++;
		usleep(1000);
	}
	i = 0;
	while (i < s->nphilo)
	{
		if (i % 2 != 0)
			pthread_create(&s->id[i], NULL, &ft_runphilos, (void *)&philo[i]);
		i++;
		usleep(1000);
	}
	ft_checkdeath(s, philo);
	i = 0;
	while (i < s->nphilo)
	{
		pthread_join(s->id[i], NULL);
		i++;
	}
}

int	ft_startphilos(t_philos *s)
{
	t_philostats	*philo;

	philo = (t_philostats *)malloc(s->nphilo * sizeof(t_philostats));
	s->id = (pthread_t *)malloc((s->nphilo) * sizeof(pthread_t));
	ft_startphilo(philo, s);
	ft_initsem(s);
	s->startime = ft_gettime();
	ft_createpthreads(s, philo);
	ft_destroysem(s);
	free(philo);
	return (1);
}

void	*ft_runphilos(void *arg)
{
	t_philostats	*philo;

	philo = (t_philostats *)arg;
	philo->lastmeal = ft_gettime();
	while (!philo->data->isdprint)
	{
		sem_wait(philo->data->death);
		if (philo->data->isdprint)
		{
			sem_post(philo->data->death);
			break ;
		}
		sem_post(philo->data->death);
		ft_philoeat(philo);
		sem_wait(philo->data->death);
		if (philo->data->isdprint)
		{
			sem_post(philo->data->death);
			break ;
		}
		sem_post(philo->data->death);
		ft_philosleep(philo);
	}
	return (0);
}
