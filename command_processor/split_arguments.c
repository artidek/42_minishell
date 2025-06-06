/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:06:04 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 10:58:17 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	single_quote_string(char **res, char *arg, int *i)
{
	int	j;

	j = 0;
	while (arg[j])
	{
		if (arg[j] == '\'' && j > 0)
		{
			*i += 1;
			add_to_str(res, 1, &arg[j]);
			return ;
		}
		if (arg[j])
			add_to_str(res, 1, &arg[j]);
		j++;
		*i += 1;
	}
}

static void	double_quote_string(char **res, char *arg, int *i)
{
	int	j;

	j = 0;
	while (arg[j])
	{
		if (arg[j] == '\"' && j > 0)
		{
			*i += 1;
			add_to_str(res, 1, &arg[j]);
			return ;
		}
		if (arg[j])
			add_to_str(res, 1, &arg[j]);
		j++;
		*i += 1;
	}
}

static void	extract_inner_str(char **res, char *arg, int *i)
{
	if (*arg == 34)
	{
		double_quote_string(res, arg, i);
	}
	else
		single_quote_string(res, arg, i);
}

static void	extract_arg(char *arg, char **res, t_args **args)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\"' || arg[i] == '\'')
		{
			extract_inner_str(res, &arg[i], &i);
			update_args(res, args);
		}
		if (*res && arg[i] && arg[i] == ' ')
			update_args(res, args);
		if (arg[i])
			extract_outer_string(res, &arg[i], &i, args);
	}
	update_args(res, args);
}

char	**split_arguments(char *arguments)
{
	t_args	*args;
	char	*res;
	char	*temp;
	char	**argv;

	args = NULL;
	res = NULL;
	if (!arguments || !*arguments)
		return (NULL);
	temp = ft_strtrim(arguments, " ");
	extract_arg(temp, &res, &args);
	if (res)
		free(res);
	free(temp);
	argv = create_argv(&args);
	clear_list_a(&args, del_a);
	return (argv);
}
