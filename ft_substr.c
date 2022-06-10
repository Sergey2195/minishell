/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:35:19 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 12:42:02 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	if ((size_t)start >= ft_strlen(s))
	{
		res = (char *)malloc(sizeof(char));
		res[0] = '\0';
		return (res);
	}
	if (ft_strlen(s) >= len)
		res = (char *)malloc(sizeof(char) * len + 1);
	else
		res = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < (unsigned int)len && s[start])
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}
