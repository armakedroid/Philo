/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:32:52 by argharag          #+#    #+#             */
/*   Updated: 2025/07/26 19:32:53 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_params
{
	int				n_ph;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_cnt;
	pthread_mutex_t	print_lock;
	long			start_ms;
	pthread_mutex_t	*noone;
	int				someone_died;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	meal_lock;
}					t_params;

typedef struct s_philo
{
	int				id;
	long			last_meal_ms;
	int				eat_count;
	t_params		*pm;
	pthread_t		thread;
}					t_philo;

typedef struct s_var
{
	t_philo		*ph;
	t_params	*p;
	long		current;
	int			left_fork;
	int			right_fork;
	int			is_first;
	int			is_second;
}				t_var;

int					ft_isdigit(int c);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
long				ft_atoi(const char *str);
size_t				ft_strlen(const char *s);
void				print_message(t_params *p, int i, char *str, long time);
long				now_s(void);
void				smart_sleep(long ms, t_params *p);
void				*dinner(void *arg);
int					check_death(t_philo *philos, t_params *p);
void				*dinner(void *arg);
long				now_s(void);
void				error(char *str);
void				free_all(t_params *params, t_philo *philos);

#endif
