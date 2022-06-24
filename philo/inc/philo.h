/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgregory <cgregory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:25:56 by cgregory          #+#    #+#             */
/*   Updated: 2022/06/23 09:04:17 by cgregory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/syscall.h>
# include <sys/types.h>

typedef struct s_rules	t_rules;

typedef struct s_phil
{
	int					phil_id;
	int					x_ate;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*status;
	unsigned long		last_meal;
	unsigned long		deadline;
	t_rules				*rules;
	pthread_t			thread_id;
	struct timeval		tv;
}	t_phil;

typedef struct s_rules
{
	long				phil_num;
	long				life_time;
	long				eat_time;
	long				sleep_time;
	long				eat_count;
	int					death_note;
	int					all_ate;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*status;
	t_phil				*phils;
	pthread_mutex_t		writing;
	pthread_mutex_t		globe_var;
	pthread_t			monitor_thread;
	struct timeval		tv;
	unsigned long		curr_time;
	unsigned long		launch_time;
	unsigned long		create_time;
	unsigned long		create_delay;
	unsigned long		switch_time;
	unsigned long		switch_delay;
}	t_rules;

unsigned long	timestamp(struct timeval *tv);
int				error_manager(int error);
void			write_error(char *str);
char			ft_atoi_char(const char *str, long *nmbr);
void			action_print(t_rules *rules, int id, char *string);
int				args_not_valid(int argc, char **argv);
int				parser(t_rules *rules, char **argv);
int				init_mutex(t_rules *rules);
int				init_mutex2(t_rules *rules);
int				init_launch_phil(t_rules *rules, int i);
int				launcher(t_rules *rules);
void			exit_launcher(t_rules *rules);
void			phil_thread_prepare(t_phil *phil);
void			*phil_thread(void *void_philosopher);
void			phils_check_cycle(t_rules *rules, int i);
void			*monitor(void *void_rules);
int				ft_forks_up(t_phil *phil);
void			ft_forks_down(t_phil *phil);
int				philo_eats(t_phil *philo);
void			smart_sleep(unsigned long time, t_phil *phil);
void			smart_sleep2(unsigned long time, t_rules *rules);
#endif
