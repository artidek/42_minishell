/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:50:38 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/29 20:25:38 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*rebuild_arg(char **argv)
{
	int	i;
	char	*res;

	i = 0;
	res = NULL;
	while (argv[i])
	{
		add_to_str(&res, ft_strlen(argv[i]), argv[i]);
		i++;
	}
	return (res);
}

void	write_quotes(int write_end, char *input)
{
	char	*temp;

	temp = ft_strdup(input);
	free(input);
	input = ft_strjoin("\n", temp);
	free(temp);
	write(write_end, input, ft_strlen(input) + 1);
	free(input);
}

int	stop_quotes(char quote, char *input)
{
	int i;
	int num_quotes;

	i = 0;
	num_quotes = 0;
	while (input[i])
	{
		if (input[i] == quote)
			num_quotes++;
		i++;
	}
	if (num_quotes % 2 != 0 )
		return (1);
	return (0);
}
