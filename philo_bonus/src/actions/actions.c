/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:09:56 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/19 15:18:39 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philoeat(t_philostats *philo)
{
	sem_wait(philo->data->forks);
	ft_print(philo, "has taken a fork");
	if (philo->data->nphilo == 1)
		usleep(philo->data->tdie * 1000);//CHECK WHAT HAPPENDS FOR 1
	else
	{
		sem_wait(philo->data->forks);
		ft_print(philo, "has taken a fork");
	}
	sem_wait(philo->data->meal);
	philo->lastmeal = ft_gettime();
	sem_post(philo->data->meal);
	ft_print(philo, "is eating");
	usleep(philo->data->teat * 1000);
	philo->nmeals++;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	return (NULL);
}

void	*ft_philosleep(t_philostats *philo)
{
	ft_print(philo, "is sleeping");
	usleep(philo->data->tsleep * 1000);
	ft_print(philo, "is thinking");
	return (NULL);
}

void	*ft_checkdeath(t_philos *s, t_philostats	*philo)
{
	int				i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < s->nphilo)
		{
			if (ft_checkisdeath(&philo[i]) == 0)
				return (NULL);
			i++;
		}
	}
}

int	ft_checkisdeath(t_philostats *philo)
{
	sem_wait(philo->data->meal);
	if (ft_gettime() - philo->lastmeal > philo->data->tdie)
	{
		sem_wait(philo->data->print);
		ft_printf("%i %i", ft_gettime() - philo->data->startime,
			(*philo).id + 1);
		ft_printf(" died\n");
		sem_post(philo->data->print);
		sem_wait(philo->data->death);
		philo->data->isdprint = 1;
		sem_post(philo->data->death);
		sem_post(philo->data->meal);
		return (0);
	}
	sem_post(philo->data->meal);
	if (philo->data->tmusteat != -1 && philo->nmeals >= philo->data->tmusteat)
	{
		philo->data->isdprint = 1;
		return (0);
	}
	return (1);
}
