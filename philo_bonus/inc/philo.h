/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:57:12 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/19 14:52:47 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/libft.h"
# include <pthread.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

typedef struct s_philos
{
	int				nphilo;
	int				tdie;
	int				teat;
	int				tsleep;
	int				tmusteat;
	int				isdead;
	int				isdprint;
	int				startime;
	pthread_t		*id;
	sem_t			*death;
	sem_t			*meal;
	sem_t			*print;
	sem_t			*forks;
}	t_philos;

typedef struct s_philostats
{
	int				lastmeal;
	int				id;
	int				nmeals;
	t_philos		*data;
}	t_philostats;

void	ft_startphilo(t_philostats *philo, t_philos *s);
void	ft_initstruct(t_philos *s);
void	ft_initsem(t_philos *s);
void	ft_destroysem(t_philos *s);
void	ft_print(t_philostats *philo, char *str);
int		ft_gettime(void);
int		ft_startphilos(t_philos *s);
int		ft_isformatted(char **argv, int argc, t_philos *s);
void	*ft_philoeat(t_philostats *philo);
void	*ft_philosleep(t_philostats *philo);
void	*ft_runphilos(void *arg);
void	*ft_checkdeath(t_philos *s, t_philostats	*philo);
int		ft_checkisdeath(t_philostats *philo);

#endif
