/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:25:44 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/21 11:01:33 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_startphilo(t_philostats *philo, t_philos *s)
{
	int	i;

	i = 0;
	while (i < s->nphilo)
	{
		pthread_mutex_init(&philo[i].meal, NULL);
		pthread_mutex_init(&philo[i].numeal, NULL);
		philo[i].id = i;
		philo[i].data = s;
		philo[i].lastmeal = 0;
		philo[i].nmeals = 0;
		if (i == 0)
			philo[i].r_fork = &s->forks[s->nphilo - 1];
		else
			philo[i].r_fork = &s->forks[i - 1];
		philo[i].l_fork = &s->forks[i];
		i++;
	}
}

void	ft_initstruct(t_philos *s)
{
	s->nphilo = 0;
	s->tdie = 0;
	s->teat = 0;
	s->tsleep = 0;
	s->tmusteat = -1;
	s->isdead = 0;
	s->isdprint = 0;
	s->startime = 0;
}

void	ft_initmutex(t_philos *s)
{
	int	i;

	i = 0;
	pthread_mutex_init(&s->print, NULL);
	pthread_mutex_init(&s->death, NULL);
	while (i < s->nphilo)
	{
		pthread_mutex_init(&s->forks[i], NULL);
		i++;
	}
}

void	ft_destroymutex(t_philos *s, t_philostats *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&s->print);
	pthread_mutex_destroy(&s->death);
	while (i < s->nphilo)
	{
		pthread_mutex_destroy(&philo[i].meal);
		pthread_mutex_destroy(&philo[i].numeal);
		pthread_mutex_destroy(&s->forks[i]);
		i++;
	}
	free(s->id);
	free(s->forks);
}
