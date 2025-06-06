/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:32:29 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 14:52:11 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_home(char **pwd, int len)
{
	int		i;
	char	*str1;
	char	*str2;
	char	*temp;

	i = 0;
	str1 = ft_strdup("/");
	str2 = NULL;
	while (i < len)
	{
		if (!str2)
			str2 = ft_strdup(pwd[i]);
		else
		{
			temp = ft_strdup(str2);
			free(str2);
			str2 = ft_strjoin(temp, "/");
			free(temp);
			temp = ft_strdup(str2);
			free(str2);
			str2 = ft_strjoin(temp, pwd[i]);
		}
		i++;
	}
	return (build_str(&str1, &str2, "$ "));
}

static char	*get_home_inner(char **pwd, int len_home, int len_pwd)
{
	char	*str1;
	char	*str2;
	char	*temp;

	str1 = ft_strdup("~/");
	temp = NULL;
	str2 = NULL;
	while (len_home < len_pwd)
	{
		if (!str2)
			str2 = ft_strdup(pwd[len_home]);
		else
		{
			temp = ft_strdup(str2);
			free(str2);
			str2 = ft_strjoin(temp, "/");
			free(temp);
			temp = ft_strdup(str2);
			free(str2);
			str2 = ft_strjoin(temp, pwd[len_home]);
			free(temp);
		}
		len_home++;
	}
	return (build_str(&str1, &str2, "$ "));
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

static char	*build_prompt(char *logname, char *hostname, char **pwd,
		char **home)
{
	char	*temp1;
	char	*temp2;
	char	*prompt;
	int		arrlen_pwd;
	int		arrlen_home;

	temp1 = get_name(logname, hostname);
	arrlen_pwd = arr_len(pwd);
	arrlen_home = arr_len(home);
	temp2 = NULL;
	if (arrlen_pwd - arrlen_home > 0 && arrlen_pwd > 0)
		temp2 = get_home_inner(pwd, arrlen_home, arrlen_pwd);
	else if (arrlen_pwd - arrlen_home < 0 && arrlen_pwd > 0)
		temp2 = get_home(pwd, arrlen_pwd);
	else if (arrlen_pwd == 0)
		temp2 = ft_strdup("/$ ");
	else if (arrlen_pwd - arrlen_home == 0)
		temp2 = ft_strdup("~$ ");
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
	char	**hostname;
	char	**home;

	prompt = NULL;
	logname = getenv("LOGNAME");
	pwd = get_pwd();
	home = ft_split(getenv("HOME"), '/');
	hostname = ft_split(HSTNM, '.');
	prompt = build_prompt(logname, hostname[0], pwd, home);
	free_arr(hostname);
	free_arr(pwd);
	free_arr(home);
	return (prompt);
}
