/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:51:40 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/02 12:46:01 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

static t_list	*find_last_entry(t_list *vars)
{
	char	**lk_up_arr;

	while (vars)
	{
		lk_up_arr = ft_split(vars->content, '=');
		if (lk_up_arr[0][0] == '?')
			return (vars);
		free_arr(lk_up_arr);
		vars = vars->next;
	}
	return (vars);
}

void	handle_exit(int status, struct sigaction sa_orig, t_main_dat *main_data)
{
	int	st;
	char *num_to_str;
	char	*new_entry;
	t_list *lst_entry;

	st = WEXITSTATUS(status);
	num_to_str = ft_itoa(st);
	new_entry = NULL;
	lst_entry = find_last_entry(main_data->vars);
	add_to_str(&new_entry, ft_strlen("?="), "?=");
	add_to_str(&new_entry, ft_strlen(num_to_str), num_to_str);
	free(lst_entry->content);
	lst_entry->content = ft_strdup(new_entry);
	free(new_entry);
	printf("exit_code %s\n", num_to_str);
	free(num_to_str);
	enable_echoctl();
	sig_restore(&sa_orig);
}
