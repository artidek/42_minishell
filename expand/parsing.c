/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:11:25 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/28 23:30:01 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	s_q_inner(char *arg, int *j, int *i, t_expand **exp)
{
	int	a;
	char	*str;

	a = 1;
	while (arg[a])
	{
		if (arg[a] != '$')
			add_to_str(&str, 1, arg + a);
		if (arg[a] == ' ' || arg[a] == '$')
		{
			update_expand(exp, &str, 1);
			return;
		}
		a++;
		*j += 1;
		*i += 1;
	}
}

static void	s_q_expand(char *arg, t_expand **exp, int *i)
{
	int	j;
	char	*str;

	j = 0;
	str = NULL;
	while (arg[j] && arg[j] != '\'')
	{
		if (arg[j] != '$')
		{
			add_to_str(&str, 1, &(*arg) + j);
			j++;
			*i += 1;
		}
		if (arg[j] && arg[j] == ' ')
		{
			update_expand(exp, &str, 1);
			j++;
			*i += 1;
		}
		if (arg[j] && arg[j] == '$')
			s_q_inner(arg + j, &j, i, exp);
	}
}

static void	single_quote(char **arg, t_expand **exp)
{
	int	i;
	char	*str;
	
	i = 0;
	str = NULL;
	while (*arg[i])
	{
		if (*arg[i] == '\'')
		{
			skip_sp(&str, (*arg) + (i + 1), &i);
			if (*arg[i] == '$' && *arg[i + 1] != ' ')
			{
				add_expand(exp, new_expand(ft_strdup(strdup(str)), 0));
				free(str);
				str = NULL;
				s_q_expand((*arg) + (i + 1), exp, &i);
			}
		}
		if (*arg[i])
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
		single_quote(&(*arg) + 1, &exp);
	//else
		//extr_exp (arg, &exp);
	expand(&exp, main_data);
	join_expanded(arg, exp);
	printf("arg %s\n", *arg);
	clear_expand(&exp);
}
