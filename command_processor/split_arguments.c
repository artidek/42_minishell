/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:06:04 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/24 23:56:10 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*single_quote_string(char **arg, int size)
{
	char	*res;
	char	*ret_res;

	res = malloc(sizeof(char) * size + 1);
	ret_res = res;
	while (*(*arg))
	{
		*res = *(*arg);
		res++;
		(*arg)++;
		if (*(*arg) == 39)
		{
			*res = *(*arg);
			res++;
			(*arg)++;
			break;
		}
	}
	*res = 0;
	return (ret_res);
}

static char	*double_quote_string(char **arg, int size)
{
	int		i;
	char	*res;

	i = 0;
	res = malloc(sizeof(char) * size + 1);
	while (*(*arg))
	{
		res[i] = *(*arg);
		i++;
		(*arg)++;
		if (*(*arg) == 34)
		{
			res[i] = *(*arg);
			i++;
			(*arg)++;
			break;
		}
	}
	res[i] = 0;
	return (res);
}

static char	*extract_inner_str(char **arg, int size)
{
	char	*res;

	if (*(*arg) == 34)
	{
		res = double_quote_string(arg, size);
		return (res);
	}
	else
		res = single_quote_string(arg, size);
	return (res);
}

static char	*extract_arg(char **arg, int size)
{
	char	*res;
	char	*cp_res;
	int		i;

	i = 0;
	if (*(*arg) == 34 || *(*arg) == 39)
	{
		res = extract_inner_str(arg, size);
		return (res);
	}
	res = malloc(sizeof(char) * size + 1);
	while (*(*arg) && *(*arg) != ' ')
	{
		res[i] = *(*arg);
		(*arg)++;
		i++;
	}
	res[i] = '\0';
	cp_res = ft_strdup(res);
	free(res);
	return (cp_res);
}

char	**split_arguments(char *arguments)
{
	t_args	*args;
	char		*temp;
	char		*trimed;
	char		**argv;
	int			size;

	args = NULL;
	trimed = ft_strtrim(arguments, " ");
	temp = trimed;
	size = ft_strlen(trimed);
	while (*temp)
	{
		if (*temp != ' ')
			add_node_a(&args, create_node_a(extract_arg(&temp, size)));
		if (*temp)
			temp++;
	}
	free(trimed);
	argv = create_argv(&args);
	clear_list_a(&args, del_a);
	return (argv);
}
