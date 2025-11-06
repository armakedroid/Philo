/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messege.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:25:04 by argharag          #+#    #+#             */
/*   Updated: 2025/07/26 19:25:05 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_params *p, int i, char *str, long time)
{
	pthread_mutex_lock(&p->print_lock);
	printf("%ld %d %s\n", time, i, str);
	pthread_mutex_unlock(&p->print_lock);
}
