/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:23:01 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 13:03:17 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getsize(char *src)
{
	int	i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		sz;
	char	*pi;

	pi = NULL;
	i = 0;
	sz = ft_getsize((char *)s1);
	pi = malloc(sz + 1);
	if (NULL == pi)
		return (NULL);
	while (s1[i])
	{
		*(pi + i) = *(s1 + i);
		i++;
	}
	*(pi + i) = '\0';
	return (pi);
}
