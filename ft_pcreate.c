/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pcreate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 09:58:17 by lde-mich          #+#    #+#             */
/*   Updated: 2023/04/18 12:12:05 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*ft_philo_create(t_data *data)
{
	t_philo	*tmp;
	t_philo	*philo;
	int		i;

	philo = (t_philo *) malloc(sizeof(t_philo));
	tmp = philo;
	i = 0;
	while (i < data->n_philo)
	{
		philo->data = data;
		philo->id = i + 1;
		philo->n_eat = data->n_eat;
		if (i < data->n_philo - 1)
			philo->next = (t_philo *) malloc(sizeof(t_philo));
		else
			philo->next = tmp;
		pthread_mutex_init(&philo->fork, 0);
		philo = philo->next;
		i++;
	}
	philo = philo->next;
	return (philo);
}

void	ft_thread_create(t_philo *philo)
{
	t_data		data;
	int			i;

	i = 0;
	while (i < philo->data->n_philo)
	{
		pthread_create(&philo->ph, NULL, routine, (void *)philo);
		philo = philo->next;
		i++;
	}
	pthread_create(&data.phd, NULL, ft_check_death, (void *)philo);
}

void	ft_thread_join(t_philo *philo)
{
	int			i;

	i = 0;
	while (i < philo->data->n_philo)
	{
		pthread_join(philo->ph, NULL);
		philo = philo->next;
		i++;
	}
	pthread_join(philo->ph, NULL);
}
