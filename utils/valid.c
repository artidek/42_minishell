/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:20:43 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 12:59:52 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	backslash(char *arg)
{
	int	len;

	len = 0;
	if (arg && *arg)
		len = ft_strlen(arg);
	if (len > 0)
	{
		if (arg[len - 1] == '\\' || arg[0] == '\\')
			return (1);
	}
	return (0);
}

static int	closed(char *arg, int pos, unsigned char quote)
{
	while (arg[pos])
	{
		if (arg[pos] == quote)
			return (1);
		pos++;
	}
	return (0);
}

static int	check_quotes(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == 34)
		{
			if (closed(arg, i + 1, 34))
				return (1);
			else
				return (0);
		}
		if (arg[i] == 39)
		{
			if (closed(arg, i + 1, 39))
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (1);
}

static int	check_semicol(char *arg)
{
	int	len;

	len = 0;
	if (arg && *arg)
		len = ft_strlen(arg);
	if (len > 0)
	{
		if (arg[len - 1] == ';')
			return (1);
	}
	return (0);
}

int	check_valid(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		if (check_semicol(args[i]))
		{
			ft_printf("minishell: invalid syntax--;\n");
			return (0);
		}
		if (!check_quotes(args[i]))
		{
			ft_printf("minishell: invalid syntax--quotes\n");
			return (0);
		}
		if (backslash(args[i]))
		{
			ft_printf("minishell: invalid syntax--%c\n", 92);
			return (0);
		}
		i++;
	}
	return (1);
}
