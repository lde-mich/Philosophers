/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:58:46 by lde-mich          #+#    #+#             */
/*   Updated: 2023/04/18 10:53:09 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	pthread_t		phd;
	int				n_philo;
	int				tmp_die;
	int				tmp_eat;
	int				tmp_sleep;
	struct timeval	tv_u;
	int				mstime;
	int				t;
	int				tmpdie_ini;
	int				temporanea;
	int				dead;
	int				n_eat;
}	t_data;

typedef struct s_philo
{
	pthread_mutex_t	fork;
	struct s_data	*data;
	struct s_philo	*next;
	pthread_t		ph;
	int				id;
	int				temph;
	int				n_eat;
}	t_philo;

void	*routine(void *vd_philo);
long	ft_atoi(const char *str);
t_philo	*ft_philo_create(t_data *data);
void	*ft_check_death(void *vd_philo);
void	ft_print(t_philo *philo, char *action);
int		ft_mstime(void);
void	ft_msleep(int t);
void	ft_one_philo(t_philo *philo);
void	ft_free_all(t_philo	*philo);
int		ft_check_arg(int argc, char **argv);
void	ft_thread_create(t_philo *philo);
void	ft_thread_join(t_philo *philo);

#endif