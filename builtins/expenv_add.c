/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expenv_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:16:51 by svolkau           #+#    #+#             */
/*   Updated: 2025/06/15 22:50:01 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printexport(t_shenv *en)
{
	int		i;
	char	*b;
	t_shenv	*head;

	b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	i = 0;
	while (b[i])
	{
		head = en;
		while (head)
		{
			if (head->key[0] == b[i])
			{
				if (head->value == NULL)
					ft_printf("declare -x %s\n", head->key);
				else
					ft_printf("declare -x %s=\"%s\"\n", head->key, head->value);
			}
			head = head->next;
		}
		i++;
	}
}

int	findkey(t_shenv *en, char *key)
{
	while (en)
	{
		if ((ft_strncmp(en->key, key, ft_strlen(key)) == 0)
			&& (ft_strlen(en->key) == ft_strlen(key)))
			return (0);
		en = en->next;
	}
	return (1);
}

void	freeenv(t_shenv *en)
{
	t_shenv	*next;

	if (en)
	{
		while (en)
		{
			next = en->next;
			free(en->key);
			free(en->value);
			free(en);
			en = next;
		}
	}
}

int	getposeql(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}
