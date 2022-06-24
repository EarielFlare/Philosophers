/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgregory <cgregory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:25:56 by cgregory          #+#    #+#             */
/*   Updated: 2022/06/24 07:23:12 by cgregory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/syscall.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_rules	t_rules;

typedef struct s_phil
{
	int					phil_id;
	int					x_ate;
	int					death_note;
	pid_t				thread_id;
	struct timeval		tv;
	unsigned long		curr_time;
	unsigned long		last_meal;
	unsigned long		deadline;
	pthread_t			monitor_thread;
//	pthread_mutex_t		dline_mutex;
//	pthread_mutex_t		death_mutex;
	sem_t				*dline_mutex;
	sem_t				*death_mutex;
	t_rules				*rules;
}	t_phil;

typedef struct s_rules
{
	long				phil_num;
	long				life_time;
	long				eat_time;
	long				sleep_time;
	long				eat_count;
	pthread_t			killer_thread;
	t_phil				*phils;
	sem_t				*forks2;
	sem_t				*writing2;
	sem_t				*globe_pause;
	sem_t				*death_sem;
	pid_t				thread_id;
	struct timeval		tv;
	unsigned long		launch_time;
	unsigned long		create_time;
	unsigned long		create_delay;
	unsigned long		switch_time;
	unsigned long		switch_delay;
}	t_rules;

unsigned long	timestamp(struct timeval *tv);
char			ft_atoi_char(const char *str, long *nmbr);
int				error_manager(int error);
int				args_not_valid(int argc, char **argv);
int				parser(t_rules *rules, char **argv);
int				init_mutex(t_rules *rules);
int				init_mutex2(t_rules *rules);
int				init_launch_phil(t_rules *rules, int i);
int				launcher(t_rules *rules);
int				phil_thread(t_phil *phil);
void			write_error(char *str);
void			action_print(t_phil *phil, int id, char *string);
void			exit_launcher(t_rules *rules);
void			*monitor(void *void_phil);
void			ft_forks_up(t_phil *phil);
void			ft_forks_down(t_phil *phil);
void			philo_eats(t_phil *philo);
void			smart_sleep(unsigned long time, t_phil *phil);
void			smart_sleep2(unsigned long time, t_rules *rules);
int				free_sem(t_rules *rules);
void			phil_thread_prepare(t_phil *phil);
void			phil_thread_destroy(t_phil *phil);
void			*killer(void *void_rules);
#endif
