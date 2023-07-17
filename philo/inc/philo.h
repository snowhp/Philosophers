/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:57:12 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/15 15:14:53 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/libft.h"
# include <pthread.h>
# include <sys/time.h>

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
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
}	t_philos;

typedef struct s_philostats
{
	int				lastmeal;
	int				id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_philos		*data;
}	t_philostats;

void	ft_startphilo(t_philostats *philo, t_philos *s);
void	ft_initstruct(t_philos *s);
void	ft_initmutex(t_philos *s);
void	ft_destroymutex(t_philos *s);
void	ft_freeall(t_philostats *philo, t_philos *s);
void	ft_print(t_philostats *philo, char *str);
int		ft_gettime(void);
int		ft_checklastmeal(t_philostats *philo);
int		ft_startphilos(t_philos *s);
int		ft_isformatted(char **argv, int argc, t_philos *s);
void	*ft_philoeat(t_philostats *philo);
void	*ft_philosleep(t_philostats *philo);
void	*ft_runphilos(void *arg);

#endif
