/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:44:21 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/23 12:38:22 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	str1;
	unsigned char	str2;

	if (!s1)
	{
		printf("found\n");
		return (-1);
	}
	while (n > 0)
	{
		str1 = *(unsigned char *)s1;
		str2 = *(unsigned char *)s2;
		if (str1 != str2)
		{
			if (str1 - str2 > 0)
				return (1);
			return (-1);
		}
		s1++;
		s2++;
		n--;
	}
	return (0);
}
