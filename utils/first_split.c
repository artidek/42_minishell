/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 16:31:06 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/08 18:08:12 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	update_split(t_args **args, char **arg)
{
	add_node_a(args, create_node_a(ft_strdup(*arg)));
	free(*arg);
	*arg = NULL;
}

static void	inner_str(char *str, char **arg, int *i)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] && (str[j] == '\'' || str[j] == '\"') && j > 0)
		{
			add_to_str(arg, 1, &str[j]);
			*i += 1;
			return;
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

static void	join_farg(char **arg, char *str, int *i)
{
	if (str[*i] && str[*i] != '|' && str[*i] != '\'' && str[*i] != '\"')
		add_to_str(arg, 1, &str[*i]);
	if (str[*i] && str[*i] != '\'' && str[*i] != '\"')
		*i += 1;
}

char	**first_split(char *input)
{
	int	i;
	char	*arg;
	char **res;
	t_args	*args;

	i = 0;
	args = NULL;
	res = NULL;
	arg = NULL;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			inner_str(&input[i], &arg, &i);
		if (arg && input[i] == '|')
			update_split(&args, &arg);
		join_farg(&arg, input, &i);
	}
	if (arg)
	{
		add_node_a(&args, create_node_a(ft_strdup(arg)));
		free(arg);
	}
	build_new_args(&res, args);
	clear_list_a(&args, del_a);
	return (res);
}
