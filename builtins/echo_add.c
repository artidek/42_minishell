/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:58:53 by svolkau           #+#    #+#             */
/*   Updated: 2025/06/07 12:31:10 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	checkcmd(char *strcmd, int mes)
{
	if (ft_strlen(strcmd) > 4)
	{
		ft_printf("minishell: %s: command not found\n", strcmd);
		if (mes == 1)
			free(strcmd);
		return (1);
	}
	return (0);
}

char	*trimall(char *str)
{
	if (str[0] == '\'')
		return (ft_strtrim(str, "'"));
	if (str[0] == '\"')
		return (ft_strtrim(str, "\""));
	if (str[0] == ' ')
		return (ft_strtrim(str, " "));
	return (ft_strdup(str));
}

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

void	readprintdir(char *str)
{
	DIR				*dir;
	struct dirent	*dirs;

	dir = opendir(str);
	if (dir != NULL)
	{
		dirs = readdir(dir);
		while (dirs != NULL)
		{
			if (ft_strncmp(".", dirs->d_name, ft_strlen(dirs->d_name)) != 0
				&& ft_strncmp("..", dirs->d_name, ft_strlen(dirs->d_name)) != 0
				&& dirs->d_name[0] != '.')
				ft_printf("%s", dirs->d_name);
			dirs = readdir(dir);
			if (dirs != NULL && dirs->d_name[0] != '.'
				&& ft_strncmp(".", dirs->d_name, ft_strlen(dirs->d_name)) != 0
				&& ft_strncmp("..", dirs->d_name, ft_strlen(dirs->d_name)) != 0)
				ft_printf(" ");
		}
	}
	closedir(dir);
}

void	printarreach(char **gv, int i)
{
	int		len;
	char	*str;
	char	*trimstr;

	trimstr = trimall(gv[i]);
	len = ft_strlen(trimstr);
	if (len == 0)
		len += 1;
	if (ft_strncmp("*", gv[i], len) == 0)
	{
		str = cwd();
		readprintdir(str);
		free(str);
	}
	else
		ft_printf("%s", trimstr);
	if (ft_strlen(trimstr) != 0 && ft_strncmp("*", gv[i], len) != 0
		&& gv[i + 1])
	{
		if (ft_strncmp(" ", gv[i + 1], ft_strlen(gv[i + 1])) == 0)
			ft_printf(" ");
	}
	free(trimstr);
}
