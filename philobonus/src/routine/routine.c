/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:25:44 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/17 15:31:17 by tde-sous         ###   ########.fr       */
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

void	ft_initsem(t_philos *s)
{
	sem_unlink("forks");
	s->forks = sem_open("forks", O_CREAT, 0664, s->nphilo);
	sem_unlink("print");
	s->print = sem_open("print", O_CREAT, 0664, 1);
}

void	ft_destroymutex(t_philos *s)
{
	sem_close(s->forks);
	sem_close(s->print);
	free(s->id);
}
