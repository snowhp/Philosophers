/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:57:12 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/12 13:22:38 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

typedef struct s_philos
{
	int	nphilo;
	int	tdie;
	int	teat;
	int	tsleep;
	int	tmusteat;
}	t_philos;
