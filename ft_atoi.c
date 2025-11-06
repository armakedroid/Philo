/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:32:36 by argharag          #+#    #+#             */
/*   Updated: 2025/07/26 19:32:37 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	long	nbr;
	int		i;

	i = 0;
	nbr = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	if (!ft_isdigit(nbr) && nbr < 0)
		return (-1);
	if (nbr < INT_MIN || nbr > INT_MAX)
		return (-1);
	return (nbr);
}
/*
int	main(void) {
	char nbr[] = " -4654\n5a465456 6546554655sgh";
	printf("%d\n", atoi(nbr));
	printf("%d", ft_atoi(nbr));
}
*/
