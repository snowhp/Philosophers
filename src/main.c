/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:24:30 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/14 16:30:53 by tde-sous         ###   ########.fr       */
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

int	ft_gettime()
{
	struct timeval currentTime;

	if (gettimeofday(&currentTime, NULL) != 0)
		return (ft_printf("Error getting time"), 0);
	return (currentTime.tv_sec * 1000 + currentTime.tv_usec / 1000);
}

void	*ft_philoeat(t_philostats *philo)
{
	/* Take Left Fork*/
	if (pthread_mutex_lock(philo->l_fork) != 0)
		return (ft_printf("Failed to lock a mutex"), NULL);
	/* Block print*/
	if (pthread_mutex_lock(&philo->data->print) != 0)
		return (ft_printf("Failed to lock a mutex"), NULL);

	ft_printf("%i %i has taken a fork\n", ft_gettime(), (*philo).id + 1);
	/*Unblock print*/
	if (pthread_mutex_unlock(&philo->data->print) != 0)
		return (ft_printf("Failed to lock a mutex"), NULL);
	/* Take Right Fork*/
	if (pthread_mutex_lock(philo->r_fork) != 0)
		return (ft_printf("Failed to lock a mutex"), NULL);
	/* Block print*/
	if (pthread_mutex_lock(&philo->data->print) != 0)
		return (ft_printf("Failed to lock a mutex"), NULL);

	ft_printf("%i %i has taken a fork\n", ft_gettime(), (*philo).id + 1);

	ft_printf("%i %i is eating\n", ft_gettime(), (*philo).id + 1);
	if (pthread_mutex_unlock(&philo->data->print) != 0)
		return (ft_printf("Failed to lock a mutex"), NULL);
	usleep(philo->data->teat);
	if (pthread_mutex_unlock(philo->l_fork) != 0)
		return (ft_printf("Failed to lock a mutex"), NULL);
	if (pthread_mutex_unlock(philo->r_fork) != 0)
		return (ft_printf("Failed to lock a mutex"), NULL);
	philo->lastmeal = ft_gettime();
	return NULL;
}

void	*ft_runphilos(void *arg)
{
	t_philostats philo;

	philo = *(t_philostats*)arg;
	philo.lastmeal = ft_gettime();//Save join time
	while (!philo.data->isdead)
	{
		ft_philoeat(&philo);
		break ;
		/* ft_philosleep();
		ft_philothink(); */
	}
	if (pthread_mutex_lock(&philo.data->print) != 0)
		return (ft_printf("Failed to lock a mutex"), NULL);
	//ft_printf("Hello i am philo %i\n", philo.id + 1);
	if (pthread_mutex_unlock(&philo.data->print) != 0)
		return (ft_printf("Failed to unlock a mutex"), NULL);
	return (0);
}


int	ft_startphilos(t_philos *s)
{
	int	i;
	t_philostats	*philo;

	philo = (t_philostats *)malloc(s->nphilo * sizeof(t_philostats));
	s->id = (pthread_t *)malloc(s->nphilo * sizeof(pthread_t));
	s->forks = (pthread_mutex_t *)malloc(s->nphilo * sizeof(pthread_mutex_t));
	ft_startphilo(philo, s);
	i = 0;
	ft_initmutex(s);
	while (i < s->nphilo)
	{
		if (pthread_create(&s->id[i], NULL, &ft_runphilos, &philo[i]) != 0)
			return (ft_printf("Failed to create a thread"), 0);
		i++;
		usleep(10);//Time to let the philo's seat at the table
	}
	i = 0;
	while (i < s->nphilo)
	{
		if (pthread_join(s->id[i], NULL) != 0)
			return (ft_printf("Failed to join thread"), 0);
		i++;
	}
	ft_destroymutex(s);
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
