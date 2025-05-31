/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:35:30 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/31 11:49:22 by aobshatk         ###   ########.fr       */
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
	int	i;
	t_args	*new_args;
	
	i = 0;
	new_args = NULL;
	while (arg[i])
	{
		if (arg[i] && arg[i][0])
			add_node_a(&new_args, create_node_a(ft_strdup(arg[i])));
		i++;
	}
	return (nw_argv(new_args));
}

static void	o_q_s_rem(char **arg)
{
	int	i;
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
		*arg = ft_strdup (str);
		free(str);
	}
}

static void	full_clean(char **arg)
{
	char	*trimmed;
	char	*str;
	int	i;

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
		free(trimmed);
		free(str);
	}
	else if (trimmed && !*trimmed)
	{
		empty_str(arg);
		free(trimmed);
	}
}

void	clean_up_arg(char ***arg)
{
	int	i;

	i = 0;
	int j = 0;
	if (**arg && ft_strncmp((*arg)[i], "echo", ft_strlen((*arg)[i])) == 0
		&& ft_strncmp((*arg)[i], "echo", ft_strlen("echo")) == 0)
	{
		while ((*arg)[i])
		{
			o_q_s_rem(&(*arg)[i]);
			i++;
		}
	}
	else
	{
		while ((*arg)[i])
		{
			full_clean(&(*arg)[i]);
			i++;
		}
	}
	while ((*arg)[j])
	{
		printf("arg %s\n", (*arg)[j]);
		j++;
	}
	*arg = rebuild_arg(*arg);
}
