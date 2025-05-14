/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:39:37 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/14 18:51:25 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cmd_proc.h"

static int	is_special(char *c, t_charset **set)
{
	char	*ascii_set;
	int	i;

	ascii_set = ("abtnvfr");
	i = 0;
	while (ascii_set[i])
	{
		if (ascii_set[i] == *c)
		{
			add_charset(&set, new_charset((i + 8) - 1));
			return (1);
		}
	}
	return (0);
}

static int	check_delim(char ch, char *delim_set)
{
	while (*delim_set)
	{
		if (ch == *delim_set)
			return (1);
		delim_set++;
	}
	return (0);
}

t_charset	*extract_string(char *str, char *delim_set)
{
	t_charset	*charset;
	int	*count;

	charset = NULL;
	count = malloc(sizeof(int));
	if (!count)
		return (NULL);
	while (*str)
	{
		if (check_delim(*str, delim_set))
			break;
		if (*str == '\\')
		{
			if(is_special((str + 1), &charset));
				str++;
		}
		add_charset(&charset, new_charset(*str));
		if (!charset)
			return;
		*count += 1;
		str++;
	}
	return (charset);
}
