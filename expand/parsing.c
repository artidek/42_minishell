/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:11:25 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/08 10:42:53 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	n_q_inner(char *arg, int *i, t_expand **exp)
{
	int		j;
	char	*str;

	j = 1;
	*i += 1;
	str = NULL;
	while (arg[j] && arg[j] != '\"' && arg[j] != '\'' && arg[j] != ' ')
	{
		if (!dollar_check(arg, exp, &str, j))
		{
			*i += 1;
			return ;
		}
		if (arg[j] && arg[j] == '$' && j > 0)
		{
			update_expand(exp, &str, 1);
			return ;
		}
		j++;
		*i += 1;
	}
	update_expand(exp, &str, 1);
}

static void	no_quote(char **arg, t_expand **exp)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while ((*arg)[i])
	{
		if ((*arg)[i] == '$')
		{
			if (str)
				update_expand(exp, &str, 0);
			n_q_inner(&(*arg)[i], &i, exp);
		}
		if ((*arg)[i] && (*arg)[i] != '$')
		{
			add_to_str(&str, 1, &(*arg)[i]);
			i++;
		}
	}
	if (str)
		update_expand(exp, &str, 0);
}

static void	double_quote(char **arg, t_expand **exp)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while ((*arg)[i])
	{
		if ((*arg)[i] == '\'' && i > 0)
		{
			add_to_str(&str, 1, (*arg) + i);
			update_expand(exp, &str, 0);
			s_q_expand(&(*arg)[i], exp, &i);
		}
		if ((*arg)[i] == '$')
		{
			update_expand(exp, &str, 0);
			n_q_inner(&(*arg)[i], &i, exp);
		}
		if ((*arg)[i] != '$')
		{
			add_to_str(&str, 1, (*arg) + i);
			i++;
		}
	}
	upd_str(exp, &str);
}

static void	single_quote(char **arg, t_expand **exp)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while ((*arg)[i])
	{
		if ((*arg)[i] == '\'' && i > 0)
			s_q_expand(&(*arg)[i], exp, &i);
		if ((*arg)[i])
		{
			add_to_str(&str, 1, (*arg) + i);
			i++;
		}
	}
	update_expand(exp, &str, 0);
}

void	expandable(char **arg, t_main_dat *main_data)
{
	t_expand	*exp;

	exp = NULL;
	if (**arg == '\'')
		single_quote(arg, &exp);
	else if (**arg == '\"')
		double_quote(arg, &exp);
	else
		no_quote(arg, &exp);
	expand(&exp, main_data);
	join_expanded(arg, exp);
	clear_expand(&exp);
}
