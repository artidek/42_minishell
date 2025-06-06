/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 00:24:29 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 12:37:28 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**nw_argv(t_args *new_args)
{
	int		len;
	int		i;
	t_args	*temp;
	char	**new_arg;

	len = 0;
	i = 0;
	temp = new_args;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	new_arg = malloc(sizeof(char *) * (len + 2));
	temp = new_args;
	while (temp)
	{
		new_arg[i] = ft_strdup(temp->arg);
		i++;
		temp = temp->next;
	}
	new_arg[i] = NULL;
	clear_list_a(&new_args, del_a);
	return (new_arg);
}
