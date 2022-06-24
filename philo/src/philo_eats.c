/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgregory <cgregory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:24:14 by cgregory          #+#    #+#             */
/*   Updated: 2022/06/22 21:29:38 by cgregory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eats(t_phil *phil)
{
	t_rules	*rules;

	rules = phil->rules;
	if (!ft_forks_up(phil))
		return (0);
	phil->last_meal = timestamp(&phil->tv);
	pthread_mutex_lock(phil->status);
	phil->deadline = phil->last_meal + rules->life_time;
	pthread_mutex_unlock(phil->status);
	action_print(rules, phil->phil_id, "is eating");
	smart_sleep(rules->eat_time, phil);
	pthread_mutex_lock(phil->status);
	(phil->x_ate)++;
	pthread_mutex_unlock(phil->status);
	ft_forks_down(phil);
	return (1);
}

int	ft_forks_up(t_phil *phil)
{
	t_rules	*rules;

	rules = phil->rules;
	pthread_mutex_lock(phil->right_fork);
	action_print(rules, phil->phil_id, "has taken a fork");
	if (rules->phil_num == 1)
		return (pthread_mutex_unlock(phil->right_fork));
	pthread_mutex_lock(phil->left_fork);
	action_print(rules, phil->phil_id, "has taken a fork");
	return (1);
}

void	ft_forks_down(t_phil *phil)
{
	t_rules	*rules;

	rules = phil->rules;
	pthread_mutex_unlock(phil->left_fork);
	action_print(rules, phil->phil_id, "put down a fork");
	pthread_mutex_unlock(phil->right_fork);
	action_print(rules, phil->phil_id, "put down a fork");
}
