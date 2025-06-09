/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:35:30 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/09 13:20:21 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	build_new_args(char ***arg, t_args *args)
{
	int		len;
	int		i;
	t_args	*temp;

	i = 0;
	len = 0;
	if (*arg)
		free_arr(*arg);
	temp = args;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	temp = args;
	*arg = malloc(sizeof(char *) * (len + 1));
	while (temp)
	{
		(*arg)[i] = ft_strdup(temp->arg);
		i++;
		temp = temp->next;
	}
	(*arg)[i] = NULL;
}

static void	inner_str(char *str, char **arg, int *i, char quote)
{
	int	j;

	j = 0;
	*i += 1;
	while (str[j])
	{
		if (str[j] && str[j] == quote)
		{
			if (!*arg)
			{
				*arg = malloc(sizeof(char) * 1);
				*arg[0] = 0;
			}
			*i += 1;
			return ;
		}
		if (str[j])
			add_to_str(arg, 1, &str[j]);
		if (str[j])
		{
			j++;
			*i += 1;
		}
	}
}

static void	final_split(char ***args, char *str)
{
	int		i;
	char	*arg;
	t_args	*new_args;

	i = 0;
	new_args = NULL;
	arg = NULL;
	while (str[i])
	{
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
			inner_str(&str[i + 1], &arg, &i, str[i]);
		if (str[i] && str[i] == ' ')
		{
			skip_sign(&str[i], &i, ' ');
			add_arg(&new_args, &arg);
		}
		join_arg(&arg, str, &i);
	}
	if (arg)
	{
		add_node_a(&new_args, create_node_a(ft_strdup(arg)));
		free(arg);
	}
	build_new_args(args, new_args);
	clear_list_a(&new_args, del_a);
}

static void	rebuild_i_s(char **arg, char **nw_temp_cmd)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		add_to_str(nw_temp_cmd, ft_strlen(arg[i]), arg[i]);
		i++;
	}
}

void	clean_up_arg(char ***arg)
{
	char	*nw_temp_cmd;

	nw_temp_cmd = NULL;
	if (**arg)
	{
		rebuild_i_s(*arg, &nw_temp_cmd);
		final_split(arg, nw_temp_cmd);
		free(nw_temp_cmd);
	}
}
