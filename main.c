/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:24:30 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/12 12:54:04 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"


int	ft_isformatted(char **argv, int argc)
{
	int	nphilo;
	int	tdie;
	int	teat;
	int	tsleep;
	int	tmusteat;
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
	nphilo = ft_atoi(argv[1]);
	if (nphilo <= 0)
		return (ft_printf("Not enough philosophers\n"), 0);
	tdie = ft_atoi(argv[2]);
	if (tdie <= 0)
		return (ft_printf("Wrong time to die\n"), 0);
	teat = ft_atoi(argv[3]);
	if (teat <= 0)
		return(ft_printf("Wrong time to eat\n"), 0);
	tsleep = ft_atoi(argv[4]);
	if (tsleep <= 0)
		return(ft_printf("Wrong time to sleep\n"), 0);
	if (argv[5])
	{
		tmusteat = ft_atoi(argv[5]);
		if (tmusteat <= 0)
			return(ft_printf("Wrong time to each philo eats\n"), 0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	if (!ft_isformatted(argv, argc))
		return (0);
	return (0);
}
