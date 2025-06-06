/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:35:30 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 12:36:42 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	empty_str(char **arg)
{
	free(*arg);
	*arg = malloc(sizeof(char));
	**arg = 0;
}

static char	**rebuild_arg(char **arg)
{
	int		i;
	t_args	*new_args;

	i = 0;
	new_args = NULL;
	while (arg[i])
	{
		if (arg[i] && arg[i][0])
			add_node_a(&new_args, create_node_a(ft_strdup(arg[i])));
		i++;
	}
	free_arr(arg);
	return (nw_argv(new_args));
}

static void	o_q_s_rem(char **arg)
{
	int		i;
	char	*str;
	char	quote;

	i = 0;
	str = NULL;
	quote = 0;
	if (**arg == '\"' || **arg == '\'')
		quote = **arg;
	while ((*arg)[i] && quote)
	{
		if ((*arg)[i] != quote && (*arg)[i] != '\\')
			add_to_str(&str, 1, &(*arg)[i]);
		i++;
	}
	if (quote && !str)
		empty_str(arg);
	else if (str)
	{
		free(*arg);
		*arg = ft_strdup(str);
		free(str);
	}
}

static void	full_clean(char **arg)
{
	char	*trimmed;
	char	*str;
	int		i;

	i = 0;
	trimmed = ft_strtrim(*arg, " ");
	o_q_s_rem(&trimmed);
	str = NULL;
	if (trimmed && *trimmed)
	{
		while (trimmed[i])
		{
			if (trimmed[i] != '\n')
				add_to_str(&str, 1, &trimmed[i]);
			i++;
		}
		free(*arg);
		*arg = ft_strdup(str);
		free(str);
	}
	else if (trimmed && !*trimmed)
		empty_str(arg);
	free(trimmed);
}

void	clean_up_arg(char ***arg)
{
	int		i;
	char	*trimmed;

	i = 0;
	trimmed = ft_strtrim(*arg[0], " ");
	free(*arg[0]);
	*arg[0] = ft_strdup(trimmed);
	if (**arg && ft_strncmp(trimmed, "echo", ft_strlen(trimmed)) == 0
		&& ft_strncmp(trimmed, "echo", ft_strlen("echo")) == 0)
	{
		*arg = rebuild_arg(*arg);
		free(trimmed);
		return ;
	}
	else
	{
		while ((*arg)[i])
		{
			full_clean(&(*arg)[i]);
			i++;
		}
	}
	free(trimmed);
	*arg = rebuild_arg(*arg);
}
