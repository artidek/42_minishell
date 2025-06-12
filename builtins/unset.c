/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:15:54 by svolkau           #+#    #+#             */
/*   Updated: 2025/06/10 14:01:26 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	freecontent(t_shenv *en)
{
	if (en)
	{
		free(en->key);
		free(en->value);
		free(en);
	}
}

void	set(t_shenv *head, t_shenv *priv, t_shenv *next)
{
	if (head)
	{
		next = head->next;
		freecontent(head);
		priv->next = next;
		head = priv;
	}
}

void	delone(t_shenv **en, char *key)
{
	t_shenv	*priv;
	t_shenv	*next;
	t_shenv	*head;

	head = *en;
	priv = NULL;
	next = NULL;
	while (head)
	{
		if ((ft_strncmp(head->key, key, ft_strlen(key)) == 0)
			&& (ft_strlen(head->key) == ft_strlen(key)) && (head->export == 0))
			break ;
		priv = head;
		head = head->next;
	}
	if (priv == NULL)
	{
		*en = head->next;
		freecontent(head);
	}
	else
		set(head, priv, next);
}

int	ft_unset(t_main_dat *main_data, char **gv)
{
	int		i;
	t_shenv	*en;

	en = main_data->env_cp;
	i = 1;
	while (gv[i])
	{
		delone(&en, gv[i]);
		i++;
	}
	ft_printf("");
	return (0);
}
