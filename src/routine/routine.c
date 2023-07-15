/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:25:44 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/15 11:17:12 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_startphilo(t_philostats *philo, t_philos *s)
{
	int	i;

	i = 0;
	while (i < s->nphilo)
	{
		philo[i].id = i;
		philo[i].data = s;
		philo[i].lastmeal = 0;
		if (i == 0)
		{
			philo[i].r_fork = &s->forks[s->nphilo - 1];
			// ft_printf("I am philo %i and my r is %i", i, s->nphilo - 1);
		}
		else
		{
			philo[i].r_fork = &s->forks[i - 1];
			// ft_printf("I am philo %i and my r is %i", i, i - 1);
		}
		philo[i].l_fork = &s->forks[i];
		// ft_printf(" and my l is %i\n", i);
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
}

void	ft_initmutex(t_philos *s)
{
	int	i;

	i = 0;
	pthread_mutex_init(&s->print, NULL);
	while (i < s->nphilo)
	{
		pthread_mutex_init(&s->forks[i], NULL);
		i++;
	}

}

void	ft_destroymutex(t_philos *s)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&s->print);
	while (i < s->nphilo)
	{
		pthread_mutex_destroy(&s->forks[i]);
		i++;
	}
}

void	ft_freeall(t_philostats *philo, t_philos *s)
{
	int	i;

	i = 0;
	while (i < s->nphilo)
	{
		free(&s->forks[i]);
		i++;
	}
	free(s->forks);
	i = 0;
	while (i < s->nphilo)
	{
		free(&s->id[i]);
		i++;
	}
	free(s->id);
	i = 0;
	while (i < s->nphilo)
	{
		free(&philo[i]);
		i++;
	}
	free(philo);
}
