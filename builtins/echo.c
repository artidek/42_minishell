/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 09:17:17 by svolkau           #+#    #+#             */
/*   Updated: 2025/06/09 14:42:13 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cwd(void)
{
	char	buf[1024];
	char	*p;

	p = getcwd(buf, 1024);
	if (!p)
	{
		perror("minishell: pwd");
		return (NULL);
	}
	return (ft_strdup(p));
}

void	printarr(char **gv, int start, int mes)
{
	int	i;

	i = start;
	while (gv[i])
	{
		ft_printf("%s", gv[i]);
		if (gv[i + 1])
			ft_printf(" ");
		i++;
	}
	if (mes == 0)
		ft_printf("\n");
}

int	ft_echo(t_main_dat *main_data, char **gv)
{
	t_main_dat	temp;
	int			len;
	int			i;

	temp = *main_data;
	(void)temp;
	if (arr_len(gv) == 1)
	{
		ft_printf("\n");
		return (0);
	}
	i = 1;
	while (gv[i + 1] && !gv[i][0])
	{
		ft_printf(" ");
		i++;
	}
	len = ft_strlen(gv[i]);
	if (ft_strncmp("-n", gv[i], len) == 0 && (arr_len(gv) - 1) == i)
		ft_printf("");
	if (ft_strncmp("-n", gv[i], len) == 0)
		printarr(gv, i + 1, 1);
	if (ft_strncmp("-n", gv[i], len) != 0)
		printarr(gv, i, 0);
	return (0);
}
