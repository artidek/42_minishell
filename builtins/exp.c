/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:29:32 by svolkau           #+#    #+#             */
/*   Updated: 2025/06/10 13:28:21 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	findadd(t_shenv *en, char *key, char *value)
{
	while (en)
	{
		if ((ft_strncmp(en->key, key, ft_strlen(key)) == 0)
			&& (ft_strlen(en->key) == ft_strlen(key)))
		{
			if (value != NULL)
			{
				free(en->value);
				en->value = value;
				en->export = 0;
				free(key);
			}
			else
				free(key);
			break ;
		}
		en = en->next;
	}
}

void	addtoenv(t_shenv *en, char *key, char *value)
{
	if (findkey(en, key) == 1)
	{
		if (value == NULL)
			addback(&en, new(key, value, 1));
		else
			addback(&en, new(key, value, 0));
	}
	else
		findadd(en, key, value);
}

int	checkcharackters(char *str, int pos)
{
	int		i;

	i = 0;
	if (str[0] >= 48 && str[0] <= 57)
		return (1);
	while (str[i] && i <= pos)
	{
		if (ft_isalpha(str[i]) == 0)
		{
			if (str[i] != '=' && str[i] != '_'
				&& (str[i] < 48 || str[i] > 57))
				return (1);
		}
		i++;
	}
	return (0);
}

int	exporteachvar(t_shenv *en, char **gv)
{
	int		i;
	char	*key;
	char	*value;
	int		pos;

	i = 1;
	while (gv[i])
	{
		pos = getposeql(gv[i]);
		if (pos == 0 || checkcharackters(gv[i], pos) == 1)
		{
			ft_printf("minishell: export: %s: not a valid identifier\n", gv[i]);
			return (1);
		}
		key = ft_substr(gv[i], 0, pos);
		if (pos == (int)ft_strlen(gv[i]))
			value = NULL;
		else
			value = ft_substr(gv[i], pos + 1, ft_strlen(gv[i]) - pos - 1);
		addtoenv(en, key, value);
		i++;
	}
	return (0);
}

int	ft_export(t_main_dat *main_data, char **gv)
{
	t_shenv	*en;

	en = main_data->env_cp;
	if (arr_len(gv) == 1)
	{
		printexport(en);
		return (0);
	}
	return (exporteachvar(en, gv));
}
