/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 09:17:17 by svolkau           #+#    #+#             */
/*   Updated: 2025/06/07 10:06:50 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printarr(char **gv, int start, int mes)
{
	int	i;

	i = start;
	while (gv[i])
	{
		if ((i == start) && (ft_strncmp(" ", gv[i], ft_strlen(gv[i])) == 0))
			i++;
		if (gv[i] == NULL)
			break ;
		printarreach(gv, i);
		i++;
	}
	if (mes == 0)
		ft_printf("\n");
}

int	checkifcmdexist(char **gv, int i)
{
	char	*trimstr;
	char	*catstr;
	char	*tmp;

	if (ft_strncmp(" ", gv[i], ft_strlen(gv[i])) != 0)
	{
		catstr = ft_strdup(gv[0]);
		while (gv[i] && ft_strncmp(" ", gv[i], ft_strlen(gv[i])) != 0)
		{
			trimstr = trimall(gv[i++]);
			tmp = ft_strjoin(catstr, trimstr);
			free(catstr);
			free(trimstr);
			catstr = tmp;
		}
		if (checkcmd(catstr, 1) == 1)
			return (-1);
		free(catstr);
	}
	return (i);
}

int	gotofirstspace(char **gv, int i)
{
	int	s;
	int	q;

	s = 0;
	q = 0;
	while (gv[i] != NULL && (ft_strncmp(" ", gv[i], ft_strlen(gv[i]) == 0)
			|| ft_strncmp("\"\"", gv[i], ft_strlen(gv[i])) == 0
			|| ft_strncmp("''", gv[i], ft_strlen(gv[i])) == 0))
	{
		if (ft_strncmp(" ", gv[i], ft_strlen(gv[i])) == 0)
		{
			if (s == 1 && q == 1)
				break ;
			s = 1;
		}
		if ((ft_strncmp("\"\"", gv[i], ft_strlen(gv[i])) == 0)
			|| (ft_strncmp("''", gv[i], ft_strlen(gv[i])) == 0))
			q = 1;
		i++;
	}
	return (i);
}

void	mainecho(char **gv, int i)
{
	int		len;
	char	*trimstr;

	trimstr = trimall(gv[++i]);
	len = ft_strlen(trimstr);
	if (len == 0)
		len += 1;
	if (ft_strncmp("-n", trimstr, len) == 0 && (arr_len(gv) - 1) == i)
		ft_printf("");
	if (ft_strncmp("-n", trimstr, len) == 0)
		printarr(gv, i + 1, 1);
	if (ft_strncmp("-n", trimstr, len) != 0)
		printarr(gv, i, 0);
	free(trimstr);
}

int	ft_echo(t_main_dat *main_data, char **gv)
{
	t_main_dat	temp;
	int			i;

	temp = *main_data;
	(void)temp;
	if (checkcmd(gv[0], 0) == 1)
		return (1);
	if (arr_len(gv) == 1)
	{
		ft_printf("\n");
		return (0);
	}
	i = 1;
	i = checkifcmdexist(gv, i);
	if (i < 0)
		return (1);
	i = gotofirstspace(gv, i);
	if (gv[i] == NULL)
	{
		ft_printf("\n");
		return (0);
	}
	mainecho(gv, i);
	return (0);
}
