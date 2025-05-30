/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:45:51 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/27 13:29:35 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void freealldata(t_main_dat *main_data, char **gv, int exitcode)
{
	if (gv)
		free_arr(gv);
	if (main_data->env_cp)
		freeenv(main_data->env_cp);
	// INPUT DATA?
	if (main_data->sequence)
		clear_sequence(&(main_data->sequence));
	free(main_data);
	exit(exitcode);
}

int	ft_exit(t_main_dat *main_data, char **gv)
{
	if ((arr_len(gv) == 1) && (ft_strncmp(gv[0], "exit", ft_strlen(gv[0])) != 0))
	{
		ft_printf("‘%s’: command not found\n", gv[0]);
		return(1);
	}
	if (arr_len(gv) > 2)
	{
		ft_printf("minishell: exit: too many arguments\n");
		return(1);
	}
	if (arr_len(gv) == 2)
	{
		if (isalldigit(gv[1]) == 0)
		{
			ft_printf("minishell: exit: '%s': numeric argument required\n", gv[1]);
			freealldata(main_data, gv, 1);
		}
		else
			freealldata(main_data, gv,ft_atoi(gv[1])); //? gv[1]
	}
	freealldata(main_data, gv, 0);
	return(0);
}
