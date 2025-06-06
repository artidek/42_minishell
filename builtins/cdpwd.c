/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:20:15 by svolkau           #+#    #+#             */
/*   Updated: 2025/06/06 14:53:22 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*mygetcwd(void)
{
	char	buf[1024];
	char	*p;

	p = getcwd(buf, 1024);
	return (ft_strdup(p));
}

void	setpwd(t_shenv *en, char *oldpwd, char *keyvalue)
{
	while (en)
	{
		if (ft_strncmp(en->key, keyvalue, ft_strlen(en->key)) == 0)
			break ;
		en = en->next;
	}
	if (en)
	{
		free(en->value);
		en->value = oldpwd;
	}
}

int	ft_pwd(t_main_dat *main_data, char **gv)
{
	char		buf[1024];
	char		*p;
	t_main_dat	temp;

	temp = *main_data;
	(void)temp;
	if (ft_strlen("pwd") != ft_strlen(gv[0]))
	{
		ft_printf("minishell: %s: command not found\n", gv[0]);
		return (1);
	}
	p = getcwd(buf, 1024);
	if (!p)
	{
		perror("minishell: pwd");
		return (1);
	}
	ft_printf("%s\n", p);
	return (0);
}

int	ft_cd(t_main_dat *main_data, char **gv)
{
	t_shenv	*en;

	en = main_data->env_cp;
	if (arr_len(gv) > 2)
	{
		ft_printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (ft_strlen(gv[0]) > 2)
	{
		ft_printf("minishell: %s: command not found\n", gv[0]);
		return (1);
	}
	setpwd(en, mygetcwd(), "OLDPWD");
	if (chdir(gv[1]) != 0)
	{
		ft_printf("minishell: cd: %s: ", gv[1]);
		perror("");
		return (1);
	}
	setpwd(en, mygetcwd(), "PWD");
	return (0);
}
