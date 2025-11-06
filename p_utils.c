/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:16:36 by argharag          #+#    #+#             */
/*   Updated: 2025/07/26 19:16:39 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_params *params, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < params->n_ph)
		pthread_mutex_destroy(&params->noone[i++]);
	pthread_mutex_destroy(&params->death_lock);
	pthread_mutex_destroy(&params->print_lock);
	pthread_mutex_destroy(&params->meal_lock);
	free(params->noone);
	free(philos);
}

void	error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
	write(2, "\n", 1);
	exit(1);
}

long	now_s(void)
{
	struct timeval	time;
	long			now;

	gettimeofday(&time, NULL);
	now = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (now);
}

void	smart_sleep(long ms, t_params *p)
{
	long	start;

	start = now_s() + ms;
	while (now_s() < start)
	{
		pthread_mutex_lock(&p->death_lock);
		if (p->someone_died)
		{
			pthread_mutex_unlock(&p->death_lock);
			break ;
		}
		pthread_mutex_unlock(&p->death_lock);
		usleep(500);
	}
}
