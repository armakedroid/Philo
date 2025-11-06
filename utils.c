/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:59:40 by argharag          #+#    #+#             */
/*   Updated: 2025/07/26 19:00:06 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dinner_2(t_var *var)
{
	if (!(*var).p->someone_died)
		print_message((*var).p, (*var).ph->id + 1, "has taken a fork",
			(*var).current - (*var).p->start_ms);
	pthread_mutex_unlock(&(*var).p->death_lock);
	pthread_mutex_lock(&(*var).p->noone[(*var).is_second]);
	pthread_mutex_lock(&(*var).p->death_lock);
	(*var).current = now_s();
	if (!(*var).p->someone_died)
		print_message((*var).p, (*var).ph->id + 1,
			"has taken a fork", (*var).current - (*var).p->start_ms);
	pthread_mutex_unlock(&(*var).p->death_lock);
	pthread_mutex_lock(&(*var).p->meal_lock);
	(*var).ph->last_meal_ms = now_s();
	(*var).ph->eat_count++;
	pthread_mutex_unlock(&(*var).p->meal_lock);
	pthread_mutex_lock(&(*var).p->death_lock);
	(*var).current = now_s();
	if (!(*var).p->someone_died)
		print_message((*var).p, (*var).ph->id + 1, "is eating",
			(*var).current - (*var).p->start_ms);
	pthread_mutex_unlock(&(*var).p->death_lock);
	smart_sleep((*var).p->time_to_eat, (*var).p);
	pthread_mutex_unlock(&(*var).p->noone[(*var).is_second]);
	pthread_mutex_unlock(&(*var).p->noone[(*var).is_first]);
}

int	dinner_ut(t_var *var)
{
	(*var).left_fork = (*var).ph->id;
	(*var).right_fork = ((*var).left_fork + 1) % (*var).p->n_ph;
	if ((*var).left_fork < (*var).right_fork)
	{
		(*var).is_first = (*var).left_fork;
		(*var).is_second = (*var).right_fork;
	}
	else
	{
		(*var).is_first = (*var).right_fork;
		(*var).is_second = (*var).left_fork;
	}
	pthread_mutex_lock(&(*var).p->death_lock);
	if ((*var).p->someone_died)
	{
		pthread_mutex_unlock(&(*var).p->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&(*var).p->death_lock);
	pthread_mutex_lock(&(*var).p->noone[(*var).is_first]);
	pthread_mutex_lock(&(*var).p->death_lock);
	(*var).current = now_s();
	return (0);
}

int	dinner_3(t_var *var)
{
	if ((*var).p->must_eat_cnt > 0 && (*var).ph->eat_count
		>= (*var).p->must_eat_cnt)
		return (1);
	pthread_mutex_lock(&(*var).p->death_lock);
	(*var).current = now_s();
	if (!(*var).p->someone_died)
		print_message((*var).p, (*var).ph->id + 1, "is sleeping",
			(*var).current - (*var).p->start_ms);
	pthread_mutex_unlock(&(*var).p->death_lock);
	smart_sleep((*var).p->time_to_sleep, (*var).p);
	pthread_mutex_lock(&(*var).p->death_lock);
	if ((*var).p->someone_died)
	{
		pthread_mutex_unlock(&(*var).p->death_lock);
		return (1);
	}
	return (0);
}

void	more_ut(t_var *var)
{
	pthread_mutex_unlock(&(*var).p->death_lock);
	pthread_mutex_lock(&(*var).p->death_lock);
	(*var).current = now_s();
	if (!(*var).p->someone_died)
		print_message((*var).p, (*var).ph->id + 1,
			"is thinking", (*var).current - (*var).p->start_ms);
	pthread_mutex_unlock(&(*var).p->death_lock);
}

void	*dinner(void *arg)
{
	t_var	var;

	var.ph = (t_philo *)arg;
	var.p = var.ph->pm;
	if (var.ph->id % 2 == 0)
		smart_sleep(var.p->time_to_eat / 10, var.p);
	while (1)
	{
		if (var.p->n_ph == 1)
		{
			var.current = now_s();
			print_message(var.p, 1, "has taken a fork", 0);
			smart_sleep(var.p->time_to_die - 1, var.p);
			return (NULL);
		}
		if (dinner_ut(&var))
			break ;
		dinner_2(&var);
		if (dinner_3(&var))
			break ;
		more_ut(&var);
	}
	return (NULL);
}
