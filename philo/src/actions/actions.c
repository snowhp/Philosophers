/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:09:56 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/20 10:31:12 by tde-sous         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->meal);
	philo->lastmeal = ft_gettime();
	pthread_mutex_unlock(&philo->meal);
	ft_print(philo, "is eating");
	usleep(philo->data->teat * 1000);
	pthread_mutex_lock(&philo->numeal);
	philo->nmeals++;
	pthread_mutex_unlock(&philo->numeal);
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
	int	total;

	total = 0;
	i = 0;
	while (1)
	{
		if (total == s->nphilo - 1)
		{
			pthread_mutex_lock(&philo->data->death);
			philo->data->isdprint = 1;
			pthread_mutex_unlock(&philo->data->death);
			return (NULL);
		}
		total = 0;
		i = 0;
		while (i < s->nphilo)
		{
			if (ft_checkisdeath(&philo[i]) == 0)
				return (NULL);
			if (ft_eatall(&philo[i]))
				total++;
			i++;
		}
	}
}

int	ft_eatall(t_philostats *philo)
{
	pthread_mutex_lock(&philo->numeal);
	if (philo->data->tmusteat != -1 && philo->nmeals >= philo->data->tmusteat)
	{
		pthread_mutex_unlock(&philo->numeal);
		return (1);
	}
	pthread_mutex_unlock(&philo->numeal);
	return (0);
}

int	ft_checkisdeath(t_philostats *philo)
{
	pthread_mutex_lock(&philo->meal);
	if (ft_gettime() - philo->lastmeal > philo->data->tdie)
	{
		pthread_mutex_unlock(&philo->meal);
		pthread_mutex_lock(&philo->data->print);
		ft_printf("%i %i", ft_gettime() - philo->data->startime,
			(*philo).id + 1);
		ft_printf(" died\n");
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_lock(&philo->data->death);
		philo->data->isdprint = 1;
		pthread_mutex_unlock(&philo->data->death);
		return (0);
	}
	pthread_mutex_unlock(&philo->meal);
	return (1);
}
