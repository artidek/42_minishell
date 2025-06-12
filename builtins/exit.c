/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:45:51 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/09 11:06:14 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_last_ex(t_main_dat *main_data)
{
	int		exit_status;
	char	**splited;

	splited = ft_split(main_data->vars->content, '=');
	exit_status = ft_atoi(splited[1]);
	free_arr(splited);
	return (exit_status);
}

int	ft_exit(t_main_dat *main_data, char **gv)
{
	int	lst_ex;

	if (arr_len(gv) > 2)
	{
		ft_printf("exit: too many arguments\n");
		return (0);
	}
	if (arr_len(gv) == 1)
	{
		lst_ex = get_last_ex(main_data);
		clear_all(main_data);
		exit (lst_ex);
	}
	if (!isalldigit(gv[1]))
	{
		ft_printf("exit: wrong argument\n");
		return (0);
	}
	lst_ex = ft_atoi(gv[1]);
	clear_all(main_data);
	ft_printf("exit\n");
	exit(lst_ex);
	return (1);
}
