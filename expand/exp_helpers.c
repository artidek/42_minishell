/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:45:31 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 11:38:26 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	upd_str(t_expand **exp, char **str)
{
	if (*str)
		update_expand(exp, str, 0);
}

int	dollar_check(char *arg, t_expand **exp, char **str, int j)
{
	if (arg[j] != '$')
	{
		add_to_str(str, 1, arg + j);
		if (arg[j - 1] == '$' && arg[j] == '?')
		{
			update_expand(exp, str, 1);
			return (0);
		}
	}
	return (1);
}
