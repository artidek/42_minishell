/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:22:49 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/14 18:30:21 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cmd_proc.h"

void	clear_charset(t_charset **set)
{
	t_charset	*temp;

	temp = *set;
	while (*set)
	{
		temp = (*set)->next;
		if ((*set)->count)
			free((*set)->count);
		free(*set);
		*set = temp;
	}
}

t_charset	*new_charset(char c)
{
	t_charset	*new_set;

	new_set = malloc(sizeof(t_charset));
	if (!new_set)
		return (NULL);
	new_set->chr = c;
	new_set->next = NULL;
}

void	add_charset(t_charset **set, t_charset *new_set)
{
	t_charset	*temp;

	if (!(*set) && !new_set)
		return;
	if (!(*set)->count)
		return;
	if (!(*set))
	{
		*set = new_set;
		return;
	}
	temp = *set;
	while (temp->next)
		temp = temp->next;
	temp->next = new_set;
}
