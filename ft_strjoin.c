/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 11:02:17 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 19:31:35 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		j;
	int		i;
	int		v;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	v = ft_strlen(s1) + ft_strlen(s2);
	if (v == 0)
		v = 2;
	res = (char *)malloc(sizeof(char) * (v + 1));
	if (res == NULL)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
	{
		res[i] = s1[i];
	}
	while (s2[++j])
		res[i++] = s2[j];
	res[i] = '\0';
	return (res);
}
