/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:51:40 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 11:09:58 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_list	*find_last_entry(t_list *vars)
{
	char	**lk_up_arr;
	char	*temp;

	while (vars)
	{
		temp = (char *)vars->content;
		if (temp && temp[0])
		{
			lk_up_arr = ft_split(vars->content, '=');
			if (lk_up_arr[0][0] == '?')
			{
				free_arr(lk_up_arr);
				return (vars);
			}
		}
		free_arr(lk_up_arr);
		vars = vars->next;
	}
	return (vars);
}

void	handle_exit(t_main_dat *main_data, int status)
{
	char	*num_to_str;
	char	*new_entry;
	t_list	*lst_entry;

	num_to_str = ft_itoa(status);
	new_entry = NULL;
	lst_entry = find_last_entry(main_data->vars);
	add_to_str(&new_entry, ft_strlen("?="), "?=");
	add_to_str(&new_entry, ft_strlen(num_to_str), num_to_str);
	free(lst_entry->content);
	lst_entry->content = ft_strdup(new_entry);
	free(new_entry);
	free(num_to_str);
}
