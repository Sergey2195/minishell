/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:18:03 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 14:52:10 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memset(void *ptr, int val, size_t n)
{
	unsigned char	*tmp_ptr;
	unsigned char	tmp_val;
	size_t			i;

	tmp_ptr = ptr;
	tmp_val = val;
	i = 0;
	while (i < n)
	{
		tmp_ptr[i] = tmp_val;
		i++;
	}
	return (ptr);
}

int	ft_calloc(size_t n, size_t size, void **ret)
{
	*ret = (char *)malloc(size * n);
	if (!*ret)
		return (0);
	ft_memset(*ret, 0, (n * size));
	return (1);
}

int		ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == 0)
		return (-1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	return (s1[i] - s2[i]);
}

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}