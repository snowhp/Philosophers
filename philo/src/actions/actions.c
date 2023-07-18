/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:09:56 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/18 13:57:25 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philoeat(t_philostats *philo)
{
	pthread_mutex_lock(philo->l_fork);
	ft_print(philo, "has taken a fork");
	if (philo->data->nphilo == 1)
		usleep(philo->data->tdie * 1000);
	else
	{
		pthread_mutex_lock(philo->r_fork);
		ft_print(philo, "has taken a fork");
	}
	philo->lastmeal = ft_gettime();
	ft_print(philo, "is eating");
	usleep(philo->data->teat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
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
	int	i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < s->nphilo)
		{
			if (!ft_checkisdeath(&philo[i]))
				return (NULL);
			i++;
		}
	}
}

int	ft_checkisdeath(t_philostats *philo)
{
	if (ft_gettime() - philo->lastmeal > philo->data->tdie)
	{
		ft_print(philo, "died");
		philo->data->isdprint = 1;
		return (0);
	}
	return (1);
}

