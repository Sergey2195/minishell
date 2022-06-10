/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 16:15:11 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 18:07:05 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_sizestr(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
		{
			i++;
			if (s[i] == '\0')
				return (j);
		}
		while (s[i] != c && s[i])
			i++;
		j++;
	}
	return (j);
}

char	*ft_kek(char const *s, int z, char *res, int i)
{
	int	j;

	j = 0;
	i = i - z;
	while (j < z)
	{
		res[j] = s[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);
}

int	ft_omega(char **res, char const *s, char c, int str)
{
	int	i;
	int	j;
	int	z;

	i = 0;
	j = 0;
	z = 0;
	while (s[i] && j < str)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			z++;
		}
		res[j] = (char *)malloc(sizeof(char) * z + 1);
		if (res[j] == NULL)
			return (-j);
		ft_kek(s, z, res[j], i);
		j++;
		z = 0;
	}
	res[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		str;
	int		j;

	if (s == NULL)
		return (NULL);
	str = ft_sizestr(s, c);
	res = (char **)malloc(sizeof(char *) * (str + 1));
	if (res == NULL)
		return (NULL);
	j = ft_omega(res, s, c, str);
	if (j < 1)
	{
		j = -(j + 1);
		while (j >= 0)
		{
			free (res[j]);
			j--;
		}
		free(res);
	}
	return (res);
}
