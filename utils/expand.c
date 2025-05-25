/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:11:25 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/25 20:39:07 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	expand(char **arg, t_main_dat *main_data, char *find)
{
	t_shenv	*env;

	env = main_data->env_cp;
	while (env)
	{
		if (strncmp(find, env->key, ft_strlen(*arg)) == 0 && strncmp(find,
				env->key, ft_strlen(env->key)) == 0)
		{
			free(*arg);
			*arg = ft_strdup(env->value);
			return ;
		}
		env = env->next;
	}
	free(*arg);
	*arg = malloc(sizeof(char));
	*arg[0] = 0;
}

static int	is_expandable(char *arg)
{
	int		i;
	char	**temp;

	i = 0;
	temp = ft_split(arg, ' ');
	while (temp[i])
	{
		if (temp[i][1] && temp[i][0] == '$' && temp[i][1] != ' ')
		{
			free_arr(temp);
			return (1);
		}
		else if ((temp[i][1] && temp[i][2]) && (temp[i][0] == '\"'
				&& temp[i][1] == '$' && temp[i][2] != ' '))
		{
			free_arr(temp);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	join_expanded(char **exp, char **res)
{
	int		i;
	int		len;
	char	*temp;

	i = 1;
	len = arr_len(exp);
	init_str(res, exp);
	while (exp[i])
	{
		temp = ft_strdup(*res);
		free(*res);
		*res = ft_strjoin(temp, exp[i]);
		free(temp);
		if (i < len - 1)
		{
			temp = ft_strdup(*res);
			free(*res);
			*res = ft_strjoin(temp, " ");
			free(temp);
		}
		i++;
	}
	free_arr(exp);
}

static void	expand_multiple(char *arg, t_main_dat *main_data, char **expanded)
{
	int		i;
	char	*trimmed;
	char	**temp;

	i = 0;
	temp = ft_split(arg, ' ');
	while (temp[i])
	{
		if (temp[i][1] && temp[i][0] == '$' && temp[i][1] != ' ')
		{
			trimmed = ft_strtrim(&temp[i][1], "\"");
			expand(&temp[i], main_data, trimmed);
			free(trimmed);
		}
		else if ((temp[i][1] && temp[i][2]) && (temp[i][0] == '\"'
				&& temp[i][1] == '$' && temp[i][2] != ' '))
		{
			trimmed = ft_strtrim(temp[i], "\"");
			expand(&temp[i], main_data, &trimmed[1]);
			free(trimmed);
		}
		i++;
	}
	join_expanded(temp, expanded);
}

void	expandable(char **arg, t_main_dat *main_data)
{
	char	*expanded;

	if (**arg == '$' && *(*arg + 1) != ' ')
	{
		expand(arg, main_data, *arg + 1);
		return ;
	}
	else if (**arg == '\"')
	{
		if (is_expandable(*arg))
		{
			expand_multiple(*arg, main_data, &expanded);
			free(*arg);
			*arg = ft_strdup(expanded);
			free(expanded);
		}
	}
}
