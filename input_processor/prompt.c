/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:32:29 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/13 18:41:52 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_wd(char **pwd, int arrlen)
{
	char	*str1;
	char	*str2;

	if (arrlen > 1)
	{
		str1 = ft_strjoin("~", "/");
		str2 = ft_strjoin(str1, pwd[arrlen - 1]);
		free(str1);
		str1 = ft_strjoin(str2, "/");
		free(str2);
		str2 = ft_strjoin(str1, pwd[arrlen - 2]);
		free(str1);
		str1 = ft_strjoin(str2, "$ ");
		free(str2);
		return (str1);
	}
	str1 = ft_strjoin("~", "/");
	str2 = ft_strjoin(str1, pwd[arrlen - 1]);
	free(str1);
	str1 = ft_strjoin(str2, "$ ");
	free(str2);
	return (str1);
}

static char	*get_name(char *logname, char *hostname)
{
	char	*temp;
	char	*res;

	temp = ft_strjoin(logname, hostname);
	res = ft_strjoin(temp, ":");
	free(temp);
	return (res);
}

static char	*build_prompt(char *logname, char *hostname, char **pwd)
{
	char	*prompt;
	char	*temp1;
	char	*temp2;
	int		arrlen;

	arrlen = arr_len(pwd);
	temp1 = get_name(logname, hostname);
	temp2 = get_wd(pwd, arrlen);
	prompt = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	return (prompt);
}

char	*init_prompt(void)
{
	char	*logname;
	char	**pwd;
	char	*prompt;

	prompt = NULL;
	logname = getenv("LOGNAME");
	pwd = ft_split(getenv("PWD"), '/');
	prompt = build_prompt(logname, HSTNM, pwd);
	free_arr(pwd);
	return (prompt);
}
