/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:29:23 by argharag          #+#    #+#             */
/*   Updated: 2025/07/26 19:29:24 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_ut(long current_time, t_params *p, int i, long current)
{
	if (current_time > p->time_to_die)
	{
		pthread_mutex_lock(&p->death_lock);
		p->someone_died = 1;
		pthread_mutex_unlock(&p->death_lock);
		pthread_mutex_unlock(&p->meal_lock);
		print_message(p, i + 1, "died", current - p->start_ms);
		return (1);
	}
	pthread_mutex_unlock(&p->meal_lock);
	return (0);
}

int	check_death(t_philo *philos, t_params *p)
{
	int		i;
	int		count;
	long	current_time;
	long	current;

	while (1)
	{
		i = 0;
		count = 0;
		current = now_s();
		while (i < p->n_ph)
		{
			pthread_mutex_lock(&p->meal_lock);
			if (p->must_eat_cnt > 0 && philos[i].eat_count >= p->must_eat_cnt)
				count++;
			current_time = current - philos[i].last_meal_ms;
			if (check_death_ut(current_time, p, i, current))
				return (1);
			i++;
		}
		if (p->must_eat_cnt > 0 && count == p->n_ph)
			return (0);
		usleep(500);
	}
	return (0);
}

void	inital(int argc, char **argv, t_params *pm)
{
	if (argc < 5 || argc > 6)
		error("argument error");
	pm->n_ph = ft_atoi(argv[1]);
	pm->time_to_die = ft_atoi(argv[2]);
	pm->time_to_eat = ft_atoi(argv[3]);
	pm->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		pm->must_eat_cnt = ft_atoi(argv[5]);
	else
		pm->must_eat_cnt = -1;
	if (pm->n_ph <= 0 || pm->time_to_die <= 0 || pm->time_to_eat <= 0
		|| pm->time_to_sleep <= 0 || (argc == 6 && pm->must_eat_cnt <= 0))
		error("atoi error");
	pm->someone_died = 0;
	pthread_mutex_init(&pm->death_lock, NULL);
	pthread_mutex_init(&pm->print_lock, NULL);
	pthread_mutex_init(&pm->meal_lock, NULL);
	pm->noone = ft_calloc(sizeof(pthread_mutex_t), pm->n_ph);
	if (!pm->noone)
		error("malloc error");
}

void	main_help(t_params *pm, t_philo *ph)
{
	int	i;

	i = 0;
	while (i < pm->n_ph)
	{
		ph[i].id = i;
		ph[i].last_meal_ms = pm->start_ms;
		ph[i].eat_count = 0;
		ph[i].pm = &(*pm);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_params	pm;
	t_philo		*ph;
	int			i;

	inital(argc, argv, &pm);
	i = 0;
	while (i < pm.n_ph)
		pthread_mutex_init(&pm.noone[i++], NULL);
	ph = malloc(sizeof(t_philo) * pm.n_ph);
	if (!ph)
		error("malloc error");
	i = 0;
	pm.start_ms = now_s();
	main_help(&pm, ph);
	while (i < pm.n_ph)
	{
		pthread_create(&ph[i].thread, NULL, dinner, &ph[i]);
		i++;
	}
	check_death(ph, &pm);
	i = 0;
	while (i < pm.n_ph)
		pthread_join(ph[i++].thread, NULL);
	free_all(&pm, ph);
	return (0);
}
