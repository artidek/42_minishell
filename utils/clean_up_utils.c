/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 00:24:29 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/08 13:51:25 by aobshatk         ###   ########.fr       */
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
