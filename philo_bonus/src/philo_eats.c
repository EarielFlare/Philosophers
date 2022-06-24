/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgregory <cgregory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:21:25 by cgregory          #+#    #+#             */
/*   Updated: 2022/06/24 07:33:33 by cgregory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eats(t_phil *phil)
{
	t_rules	*rules;

	rules = phil->rules;
	ft_forks_up(phil);
	phil->last_meal = timestamp(&phil->tv);
//	pthread_mutex_lock(&phil->dline_mutex);
	sem_wait(phil->dline_mutex);
	phil->deadline = phil->last_meal + rules->life_time;
//	pthread_mutex_unlock(&phil->dline_mutex);
	sem_post(phil->dline_mutex);
	action_print(phil, phil->phil_id, "is eating");
	smart_sleep(rules->eat_time, phil);
//	pthread_mutex_lock(&phil->dline_mutex);
	sem_wait(phil->dline_mutex);
	(phil->x_ate)++;
//	pthread_mutex_unlock(&phil->dline_mutex);
	sem_post(phil->dline_mutex);
	ft_forks_down(phil);
}

void	ft_forks_up(t_phil *phil)
{
	t_rules	*rules;

	rules = phil->rules;
	sem_wait(rules->forks2);
	action_print(phil, phil->phil_id, "has taken a fork");
	usleep(1000);
	sem_wait(rules->forks2);
	action_print(phil, phil->phil_id, "has taken a fork");
}

void	ft_forks_down(t_phil *phil)
{
	t_rules	*rules;

	rules = phil->rules;
	sem_post(rules->forks2);
	action_print(phil, phil->phil_id, "put down a fork");
	sem_post(rules->forks2);
	action_print(phil, phil->phil_id, "put down a fork");
}
