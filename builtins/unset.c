/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:15:54 by svolkau           #+#    #+#             */
/*   Updated: 2025/05/26 17:34:03 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void freecontent(t_shenv *en)
{
	if (en)
	{
		free(en->key);
		free(en->value);
		free(en);
	}
}

void delone(t_shenv **en, char *key)
{
	t_shenv *priv = NULL;
	t_shenv *next = NULL;
	t_shenv *head;
	
	head = *en;
	while(head)
	{
		if ((ft_strncmp(head->key, key, ft_strlen(key)) == 0)
		&& (ft_strlen(head->key) == ft_strlen(key)) && (head->export == 0))
			break;
		priv = head;
		head = head->next;
	}
	if (priv == NULL)
	{	
		*en = head->next;
		freecontent(head);
	}
	else
	{
		if (head)
		{
			next = head->next;
			freecontent(head);
			priv->next = next;
			head = priv;
		}
	}
}

int ft_unset(t_main_dat *main_data, char **gv)
{
	int i;
	t_shenv *en;

	en = main_data->env_cp;
	if ((arr_len(gv) == 1) && (ft_strncmp(gv[0], "unset", ft_strlen(gv[0])) != 0))
	{
		ft_printf("‘%s’: command not found\n", gv[0]);
		return (1);
	}
	i = 1;
	while(gv[i])
	{
		delone(&en, gv[i]);
		i++;
	}
	ft_printf("");
	return(0);
}
