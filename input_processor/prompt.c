/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:32:29 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/16 15:31:48 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char **get_pwd()
{
	char buf[1024];
	char *cwd;
	char **res;

	cwd = getcwd(buf, 1024);
	res = ft_split(cwd, '/');
	return (res);
}

static char	*get_wd(char **pwd, int diff, int arrlen)
{
	char	*str1;
	char	*str2;

	str1 = NULL;
	str2 = NULL;
	if (diff > 1)
	{
		str1 = ft_strjoin("~", "/");
		str2 = ft_strjoin(str1, pwd[arrlen - diff]);
		free(str1);
		str1 = ft_strjoin(str2, "/");
		free(str2);
		str2 = ft_strjoin(str1, pwd[arrlen - (diff - 1)]);
		free(str1);
		str1 = ft_strjoin(str2, "$ ");
		free(str2);
		return (str1);
	}
	str1 = ft_strjoin("~", "/");
	str2 = ft_strjoin(str1, pwd[arrlen - diff]);
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

static char	*build_prompt(char *logname, char *hostname, char **pwd, char **home)
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
		temp2 = get_wd(pwd, arrlen_pwd - arrlen_home, arrlen_pwd);
	else if (arrlen_pwd - arrlen_home < 0 && arrlen_pwd > 0)
		temp2 = get_wd(home, arrlen_pwd, arrlen_pwd);
	else if (arrlen_pwd == 0)
		temp2 = ft_strdup("/$");
	else if (arrlen_pwd - arrlen_home == 0)
		temp2 = ft_strdup("~$");
	printf("arrlen_home %d\n", arrlen_home);
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
