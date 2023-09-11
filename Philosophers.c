/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:50:25 by lde-mich          #+#    #+#             */
/*   Updated: 2023/04/18 13:39:47 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_one_philo(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_msleep(20);
	if (philo->data->n_philo == 1)
	{
		ft_print(philo, "has taken a fork");
		while (philo->data->dead)
			;
		return ;
	}
}

void	*routine(void *vd_philo)
{
	t_philo		*philo;

	philo = (t_philo *)vd_philo;
	while (!philo->data->temporanea)
		;
	philo->temph = ft_mstime();
	ft_one_philo(philo);
	while (philo->data->dead && philo->n_eat != 0)
	{
		pthread_mutex_lock(&philo->fork);
		ft_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->next->fork);
		ft_print(philo, "has taken a fork");
		ft_print(philo, "is eating");
		philo->n_eat -= 1;
		philo->temph = ft_mstime();
		ft_msleep(philo->data->tmp_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		ft_print(philo, "is sleeping");
		ft_msleep(philo->data->tmp_sleep);
		ft_print(philo, "is thinking");
	}
	return (0);
}

int	ft_check_arg(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (write(2, "Error\nInva1id input\n", 20));
	if (!ft_atoi(argv[1]) || !ft_atoi(argv[2]) || !ft_atoi(argv[3])
		|| !ft_atoi(argv[4]))
		return (write(2, "Error\nInval2d input\n", 20));
	if (ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0
		|| ft_atoi(argv[4]) < 0)
		return (write(2, "Error\nInvali3 input\n", 20));
	if (argc == 6 && ft_atoi(argv[5]) < 0)
		return (write(2, "Error\nInvali4 input\n", 20));
	else if (argc == 6 && !ft_atoi(argv[5]))
		return (write(2, "Error\nInvali4 input\n", 20));
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo;

	data.n_eat = -1;
	if (argc == 6)
		data.n_eat = ft_atoi(argv[5]);
	if (ft_check_arg(argc, argv))
		return (0);
	data.n_philo = ft_atoi(argv[1]);
	data.tmp_die = ft_atoi(argv[2]);
	data.tmp_eat = ft_atoi(argv[3]);
	data.tmp_sleep = ft_atoi(argv[4]);
	data.tmpdie_ini = data.tmp_die;
	data.t = ft_mstime();
	data.temporanea = 0;
	philo = ft_philo_create(&data);
	data.temporanea = 1;
	data.dead = 1;
	ft_thread_create(philo);
	ft_thread_join(philo);
	ft_free_all(philo);
	return (0);
}
