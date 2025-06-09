/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 00:24:29 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/09 13:19:42 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	join_arg(char **arg, char *str, int *i)
{
	if (str[*i] && str[*i] != ' ' && str[*i] != '\'' && str[*i] != '\"')
		add_to_str(arg, 1, &str[*i]);
	if (str[*i] && str[*i] != '\'' && str[*i] != '\"')
		*i += 1;
}

void	add_arg(t_args **args, char **arg)
{
	add_node_a(args, create_node_a(ft_strdup(*arg)));
	free(*arg);
	*arg = NULL;
}
