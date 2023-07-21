/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:25:44 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/21 11:00:51 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_startphilo(t_philostats *philo, t_philos *s)
{
	int	i;
	char	*temp;

	i = 0;
	while (i < s->nphilo)
	{
		temp = ft_semname("meal", i + 1);
		sem_unlink(temp);
		philo[i].meal = sem_open(temp, O_CREAT, 0664, 1);
		free(temp);
		temp = ft_semname("numeal", i + 1);
		sem_unlink(temp);
		philo[i].numeal = sem_open(temp, O_CREAT, 0664, 1);
		free(temp);
		philo[i].id = i;
		philo[i].data = s;
		philo[i].lastmeal = 0;
		philo[i].nmeals = 0;
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

void	ft_initsem(t_philos *s)
{
	sem_unlink("forks");
	s->forks = sem_open("forks", O_CREAT, 0664, s->nphilo);
	sem_unlink("print");
	s->print = sem_open("print", O_CREAT, 0664, 1);
	sem_unlink("death");
	s->death = sem_open("death", O_CREAT, 0664, 1);
}

void	ft_destroysem(t_philos *s, t_philostats *philo)
{
	int	i;

	i = 0;
	sem_close(s->forks);
	sem_close(s->print);
	while (i < s->nphilo)
	{
		sem_close(philo[i].meal);
		sem_close(philo[i].numeal);
		i++;
	}
	free(s->id);
}

char	*ft_semname(char *str, int id)
{
	char	*result;
	char	*temp;

	temp = ft_itoa(id);
	result = ft_strjoin(str, temp);
	free(temp);
	return (result);
}
