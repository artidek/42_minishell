/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:00:47 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 11:18:13 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_expand	*new_expand(char *exp_str, int exp)
{
	t_expand	*new_exp;

	new_exp = malloc(sizeof(t_expand));
	if (!new_exp)
		return (NULL);
	new_exp->exp = exp;
	new_exp->exp_str = exp_str;
	new_exp->next = NULL;
	return (new_exp);
}

void	add_expand(t_expand **exp, t_expand *new_exp)
{
	t_expand	*temp;

	if (!*exp)
	{
		*exp = new_exp;
		return ;
	}
	temp = *exp;
	while (temp->next)
		temp = temp->next;
	temp->next = new_exp;
}

void	clear_expand(t_expand **exp)
{
	t_expand	*temp;

	while (*exp)
	{
		temp = (*exp)->next;
		if ((*exp)->exp_str)
			free((*exp)->exp_str);
		free(*exp);
		*exp = temp;
	}
}
