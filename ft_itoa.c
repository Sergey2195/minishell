/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:09:03 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 17:14:27 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_checkpos(int n, int	*a)
{
	*a += 1;
	if (n >= 0 && n <= 9)
		return ;
	else
		ft_checkpos(n / 10, a);
}

void	ft_writen(char *s, unsigned int n, int *z, int *c)
{
	int	k;

	if (n >= 0 && n <= 9)
		s[*c] = n + '0';
	else
	{
		ft_writen(s, n / 10, z, c);
		k = n % 10;
		*z += 1;
		s[*z] = k + '0';
	}
	s[*z + 1] = '\0';
}

char	*ft_pos(unsigned int n)
{
	int		i;
	int		j;
	char	*res;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	ft_checkpos(n, &i);
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (res == NULL)
		return (NULL);
	ft_writen(res, n, &j, &k);
	return (res);
}

char	*ft_neg(unsigned int n)
{
	int		i;
	int		j;
	char	*res;
	int		k;

	i = 0;
	j = 1;
	k = 1;
	ft_checkpos(n, &i);
	i += 1;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (res == NULL)
		return (NULL);
	ft_writen(res, n, &j, &k);
	res[0] = '-';
	return (res);
}

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	z;

	if (n >= 0)
	{
		z = (unsigned int)n;
		res = ft_pos(z);
	}
	else
	{
		z = n * (-1);
		res = ft_neg(z);
	}
	return (res);
}
